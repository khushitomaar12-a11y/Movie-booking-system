enum class BookingStatus { PENDING, CONFIRMED, FAILED, CANCELLED };

class Booking {
private:
    static int nextBookingId;
    string bookingId;
    Customer* customer;
    Show* show;
    vector<ShowSeat*> seats;
    double totalAmount;
    BookingStatus status;

public:
    Booking(Customer* customer, Show* show, const vector<ShowSeat*>& seats, double totalAmount)
        : customer(customer), show(show), seats(seats), totalAmount(totalAmount),
          status(BookingStatus::PENDING) {
        bookingId = "BK" + to_string(nextBookingId++);
    }

    string getBookingId() const { return bookingId; }
    Customer* getCustomer() const { return customer; }
    Show* getShow() const { return show; }
    const vector<ShowSeat*>& getSeats() const { return seats; }
    double getTotalAmount() const { return totalAmount; }
    BookingStatus getStatus() const { return status; }

    void confirm() { status = BookingStatus::CONFIRMED; }
    void fail() { status = BookingStatus::FAILED; }
    void cancel() {
        for (ShowSeat* seat : seats) seat->cancelSeat();
        status = BookingStatus::CANCELLED;
    }
};

int Booking::nextBookingId = 1001;
