-- SQLite
CREATE TABLE transactions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    symbol TEXT NOT NULL,
    shares INTEGER NOT NULL CHECK (shares > 0),
    price REAL NOT NULL,
    type TEXT NOT NULL CHECK (type IN ('BUY', 'SELL')),
    transacted TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
