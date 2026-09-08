class TicketPrinter {
public:
    void print(const Booking& booking) const {
        cout << "\n================ TICKET ================\n";
        cout << "Booking ID : " << booking.getBookingId() << "\n";
        cout << "Movie      : " << booking.getShow()->getMovie()->getTitle() << "\n";
        cout << "Screen     : Screen-" << booking.getShow()->getScreen()->getScreenNumber()
             << "\n";
        cout << "Time       : " << booking.getShow()->getStartTime() << "\n";
        cout << "Seats      : ";
        for (size_t i = 0; i < booking.getSeats().size(); ++i) {
            if (i) cout << ", ";
            cout << booking.getSeats()[i]->getNumber();
        }
        cout << "\nAmount     : Rs." << booking.getTotalAmount() << "\n";
        cout << "Status     : "
             << (booking.getStatus() == BookingStatus::CONFIRMED ? "CONFIRMED" : "NOT CONFIRMED")
             << "\n";
        cout << "=========================================\n";
    }
};
