import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    # 1. Get all shares the user owns (sum total for each stock)
    rows = db.execute("""
        SELECT symbol, SUM(shares) as total_shares
        FROM transactions
        WHERE user_id = ? AND type = 'BUY'
        GROUP BY symbol
        HAVING total_shares > 0
    """, user_id)

    holdings = []
    total_value = 0

    for row in rows:
        stock = lookup(row["symbol"])
        if stock:
            shares = row["total_shares"]
            price = stock["price"]
            value = shares * price
            total_value += value

            holdings.append({
                "symbol": stock["symbol"],
                "name": stock["name"],
                "shares": shares,
                "price": usd(price),
                "total": usd(value)
            })

    # 2. Get user's current cash
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    return render_template("index.html", holdings=holdings, cash=usd(cash), total=usd(total_value + cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # --- Validate stock symbol ---
        if not symbol:
            return apology("Missing stock symbol", 400)

        stock = lookup(symbol.upper())
        if not stock:
            return apology("Invalid stock symbol", 400)

        # --- Validate shares ---
        try:
            shares = int(shares)
            if shares <= 0:
                return apology("Shares must be a positive integer", 400)
        except:
            return apology("Invalid shares", 400)

        # --- Price calculation ---
        price = stock["price"]
        total_cost = price * shares

        # --- Get user's cash ---
        user_id = session["user_id"]
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        if user_cash < total_cost:
            return apology("Not enough cash", 400)

        # --- Update user's cash ---
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_cost, user_id)

        # --- Log the transaction ---
        db.execute("""
            INSERT INTO transactions (user_id, symbol, shares, price, type, transacted)
            VALUES (?, ?, ?, ?, 'BUY', CURRENT_TIMESTAMP)
        """, user_id, stock["symbol"], shares, price)

        # Redirect to homepage
        return redirect("/")

    # If GET, render the buy form
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]

    transactions = db.execute("""
        SELECT symbol, shares, price, type, transacted
        FROM transactions
        WHERE user_id = ?
        ORDER BY transacted DESC
    """, user_id)

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("must provide symbol", 400)
        stock = lookup(symbol)

        if stock is None:
            return apology("invalid symbol", 400)

        return render_template("quoted.html", name=stock["name"], symbol=stock["symbol"], price=usd(stock["price"]))

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        name = request.form.get("name")
        password = request.form.get("pass")
        confirme_password = request.form.get("pass2")

        # Validate form input
        if not name or not password or not confirme_password:
            return apology("Must provide all fields", 403)

        if password != confirme_password:
            return apology("Passwords do not match", 403)

        # Check if username already exists
        existing_user = db.execute("SELECT * FROM users WHERE username = ?", (name,))
        if existing_user:
            return apology("Username already exists", 403)

        # Try to insert the new user
        try:
            hashed_password = generate_password_hash(password)
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", name, hashed_password)
            return redirect("/")

        except Exception as e:
            return apology("Registration failed", 500)

    return render_template('register.html')

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Validate inputs
        if not symbol:
            return apology("Missing symbol", 400)
        if not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("Invalid shares", 400)

        shares = int(shares)

        # Get total shares the user owns
        owned = db.execute("""
            SELECT SUM(shares) as total_shares FROM transactions
            WHERE user_id = ? AND symbol = ? AND type = 'BUY'
        """, user_id, symbol)[0]["total_shares"]

        if owned is None or owned < shares:
            return apology("Too many shares", 400)

        # Get current price
        stock = lookup(symbol)
        if not stock:
            return apology("Invalid stock", 400)

        price = stock["price"]
        total_sale = price * shares

        # Add to user's cash
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", total_sale, user_id)

        # Record the transaction as a SELL
        db.execute("""
            INSERT INTO transactions (user_id, symbol, shares, price, type)
            VALUES (?, ?, ?, ?, 'SELL')
        """, user_id, symbol, shares, price)

        flash("Sold!")
        return redirect("/")

    else:
        # Get stocks the user owns
        rows = db.execute("""
            SELECT symbol FROM transactions
            WHERE user_id = ? AND type = 'BUY'
            GROUP BY symbol
            HAVING SUM(shares) > 0
        """, user_id)

        symbols = [row["symbol"] for row in rows]
        return render_template("sell.html", symbols=symbols)
