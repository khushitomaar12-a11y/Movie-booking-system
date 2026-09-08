# Movie Ticket Booking System

System Design Assignment 1 — B.Tech. CSE Semester 5, TCS-504.

A menu-driven C++ console application for a single cinema. The system supports movie/show listing, seat availability, multi-seat booking, seat-type pricing, UPI/Card/Cash payments, ticket printing, and booking cancellation.

## Features
- List currently playing movies
- List shows for a selected movie
- Display AVAILABLE / BOOKED seats
- Book one or more seats with validation
- SILVER ₹150, GOLD ₹250, PLATINUM ₹400 pricing
- UPI, Card and Cash payment options
- Failed payments release seats and do not confirm booking
- Print booking ticket
- Cancel confirmed bookings and release seats
- Handles invalid menu/seat input

## OOP Concepts
Encapsulation, abstraction, inheritance, runtime polymorphism, compile-time polymorphism, static members, `this`, composition, aggregation and association.

## SOLID
The design demonstrates SRP, OCP, LSP, ISP and DIP through separate responsibilities and the abstract `Payment` hierarchy.

## Compile and Run
```bash
g++ -std=c++17 main.cpp -o movie_booking
./movie_booking
```

On Windows:
```text
movie_booking.exe
```

## Deliberate Design Decision
No separate `SeatLayout` class is used. The layout is a view of a Show's ShowSeat objects, so `Show::displaySeats()` is sufficient and avoids unnecessary coupling.
