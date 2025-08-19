-- Keep a log of any SQL queries you execute as you solve the mystery.

-- To get the crime discription
SELECT description
FROM crime_scene_reports
WHERE street = 'Humphrey Street'
AND year = 2024 AND month = 7 AND day = 28;

-- To get transcripts of interviewers
SELECT name, transcript
FROM interviews
WHERE year = 2024 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%';

-- Review of cars leaving the bakery garage
SELECT name FROM people WHERE license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2024 AND month = 7 AND day = 28 AND hour = 10
    AND activity = 'exit' ORDER BY minute
    );

-- Check the ATM machine to know how withdraw money at this time
SELECT people.name
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_transactions.atm_location = 'Leggett Street'
AND atm_transactions.year = 2024 AND atm_transactions.month = 7
AND atm_transactions.day = 28 AND atm_transactions.transaction_type = 'withdraw';

-- Find people on the first flight out of Fiftyville tomorrow 29/7/2024
SELECT
    people.name,
    passengers.passport_number,
    people.phone_number,
    airports.city AS destination_city
FROM passengers
JOIN people ON passengers.passport_number = people.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.destination_airport_id = airports.id
WHERE flights.id = (
    SELECT id FROM flights
    WHERE origin_airport_id = (
        SELECT id FROM airports WHERE city = 'Fiftyville'
    )
    AND year = 2024
    AND month = 7
    AND day = 29
    ORDER BY hour, minute
    LIMIT 1
);

-- Calls made during this day
SELECT caller, receiver FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60;

-- Caller names
SELECT name, phone_number FROM people WHERE phone_number IN (
    SELECT caller FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60
    );

-- Receivers names
SELECT name, phone_number FROM people WHERE phone_number IN (
    SELECT receiver FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60
    );
