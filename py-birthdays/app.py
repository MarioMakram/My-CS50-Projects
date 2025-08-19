import os

# from cs50 import SQL
from flask import g, Flask, flash, jsonify, redirect, render_template, request, session
import sqlite3




# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Use SQLite database without CS50 Library
DATABASE = 'birthdays.db'

def get_db():
    db = getattr(g, '_database', None)
    if db is None:
        db = g._database = sqlite3.connect(DATABASE)
        db.row_factory = sqlite3.Row
    return db

@app.teardown_appcontext
def close_connection(exception):
    db = getattr(g, '_database', None)
    if db is not None:
        db.close()


# Configure CS50 Library to use SQLite database
# db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        name = request.form.get("friend")
        month = request.form.get("month")
        day = request.form.get("day")
        
        if not name or not month or not day:
            return redirect("/")

        print(f"Inserting: {name}, {month}, {day}")
        db = get_db()
        cursor = db.cursor()
        cursor.execute(
            "INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)",
            (name, month, day)
        )
        db.commit()
        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        db = get_db()
        cursor = db.cursor()
        birthdays = cursor.execute("SELECT * FROM birthdays").fetchall()
        return render_template("index.html", birthdays=birthdays)
    
@app.route("/delete", methods=["POST"])
def delete():
    birthday_id = request.form.get("id")
    if birthday_id:
        db = get_db()
        cursor = db.cursor()
        cursor.execute("DELETE FROM birthdays WHERE id = ?", (birthday_id,))
        db.commit()
    return redirect("/")

@app.route("/edit/<int:id>", methods=["GET",])
def edit(id):
    db = get_db()
    cursor = db.cursor()
    birthdays = cursor.execute("SELECT * FROM birthdays").fetchall()
    return render_template("index.html", birthdays=birthdays, edit_id=id)


@app.route("/update/<int:id>", methods=["POST"])
def update(id):
    name = request.form.get("name")
    month = request.form.get("month")
    day = request.form.get("day")

    if not name or not month or not day:
        return redirect("/")

    db = get_db()
    cursor = db.cursor()
    cursor.execute(
        "UPDATE birthdays SET name = ?, month = ?, day = ? WHERE id = ?",
        (name, month, day, id)
    )
    db.commit()
    return redirect("/")