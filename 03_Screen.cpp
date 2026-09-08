class Screen {
private:
    int screenNumber;
    vector<Seat> seats;

public:
    Screen(int screenNumber) : screenNumber(screenNumber) {
        // Composition: Screen creates and owns its physical Seat objects.
        for (int i = 1; i <= 4; ++i)
            seats.emplace_back("A" + to_string(i), SeatType::SILVER);
        for (int i = 1; i <= 4; ++i)
            seats.emplace_back("B" + to_string(i), SeatType::GOLD);
        for (int i = 1; i <= 2; ++i)
            seats.emplace_back("C" + to_string(i), SeatType::PLATINUM);
    }

    int getScreenNumber() const { return screenNumber; }
    const vector<Seat>& getSeats() const { return seats; }
    vector<Seat>& getSeats() { return seats; }
};
