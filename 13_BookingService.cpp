class BookingService {
private:
    PriceCalculator priceCalculator;
    TicketPrinter ticketPrinter;
    vector<Booking*> bookings;

    Payment* createPayment(int choice) {
        if (choice == 1) return new UpiPayment();
        if (choice == 2) return new CardPayment();
        if (choice == 3) return new CashPayment();
        return nullptr;
    }

public:
    ~BookingService() {
        for (Booking* booking : bookings) delete booking;
    }

    Booking* bookTicket(Customer* customer, Show* show, const vector<string>& seatNumbers,
                        int paymentChoice) {
        vector<ShowSeat*> selected;

        // Validate ALL seats before changing any state: atomic booking.
        for (const string& number : seatNumbers) {
            ShowSeat* seat = show->findSeat(number);
            if (seat == nullptr || seat->getStatus() == SeatStatus::BOOKED) {
                cout << "Booking rejected: seat " << number << " is invalid or already BOOKED.\n";
                return nullptr;
            }
            for (ShowSeat* alreadySelected : selected) {
                if (alreadySelected->getNumber() == number) {
                    cout << "Booking rejected: duplicate seat " << number << ".\n";
                    return nullptr;
                }
            }
            selected.push_back(seat);
        }

        // Temporarily reserve seats.
        for (ShowSeat* seat : selected) seat->bookSeat();

        double total = priceCalculator.calculate(selected);

        // «create» Booking
        Booking* booking = new Booking(customer, show, selected, total);

        // «create» Payment and demonstrate runtime polymorphism.
        Payment* payment = createPayment(paymentChoice);
        if (payment == nullptr) {
            for (ShowSeat* seat : selected) seat->cancelSeat();
            booking->fail();
            cout << "Invalid payment method. Seats released.\n";
            bookings.push_back(booking);
            delete payment;
            return nullptr;
        }

        bool isPaid = payment->pay(total);
        cout << "[" << payment->getMethod() << "] "
             << (isPaid ? "Payment successful." : "Payment failed.") << "\n";

        if (isPaid) {
            booking->confirm();
            bookings.push_back(booking);
            ticketPrinter.print(*booking);
        } else {
            for (ShowSeat* seat : selected) seat->cancelSeat();
            booking->fail();
            bookings.push_back(booking);
            cout << "Payment failed. Seats released and booking not confirmed.\n";
        }

        delete payment;
        return booking;
    }

    void cancelBooking(const string& bookingId) {
        for (Booking* booking : bookings) {
            if (booking->getBookingId() == bookingId) {
                if (booking->getStatus() == BookingStatus::CONFIRMED) {
                    booking->cancel();
                    cout << "Booking " << bookingId << " cancelled. Seats are AVAILABLE again.\n";
                } else {
                    cout << "Booking cannot be cancelled because it is not CONFIRMED.\n";
                }
                return;
            }
        }
        cout << "Booking ID not found.\n";
    }

    void printMyTickets(Customer* customer) const {
        bool found = false;
        for (Booking* booking : bookings) {
            if (booking->getCustomer() == customer && booking->getStatus() == BookingStatus::CONFIRMED) {
                ticketPrinter.print(*booking);
                found = true;
            }
        }
        if (!found) cout << "No confirmed tickets found.\n";
    }
};
