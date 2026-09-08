enum class SeatStatus { AVAILABLE, BOOKED };

class ShowSeat {
private:
    Seat* seat;
    SeatStatus status;

public:
    ShowSeat(Seat* seat) : seat(seat), status(SeatStatus::AVAILABLE) {}

    string getNumber() const { return seat->getNumber(); }
    SeatType getType() const { return seat->getType(); }
    SeatStatus getStatus() const { return status; }
    double getPrice() const { return Seat::price(seat->getType()); }

    bool bookSeat() {
        if (status == SeatStatus::BOOKED) return false;
        status = SeatStatus::BOOKED;
        return true;
    }

    void cancelSeat() { status = SeatStatus::AVAILABLE; }
};
