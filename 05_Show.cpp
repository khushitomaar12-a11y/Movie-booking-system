class Show {
private:
    Movie* movie;
    Screen* screen;
    string startTime;
    vector<ShowSeat> showSeats;

public:
    Show(Movie* movie, Screen* screen, string startTime)
        : movie(movie), screen(screen), startTime(startTime) {
        // Composition: Show creates ShowSeat objects for this particular show.
        for (Seat& seat : screen->getSeats())
            showSeats.emplace_back(&seat);
    }

    Movie* getMovie() const { return movie; }
    Screen* getScreen() const { return screen; }
    string getStartTime() const { return startTime; }
    vector<ShowSeat>& getShowSeats() { return showSeats; }

    ShowSeat* findSeat(const string& number) {
        for (auto& showSeat : showSeats)
            if (showSeat.getNumber() == number) return &showSeat;
        return nullptr;
    }

    void displaySeats() const {
        cout << "\nSILVER     ";
        for (const auto& s : showSeats)
            if (s.getType() == SeatType::SILVER)
                cout << s.getNumber() << (s.getStatus() == SeatStatus::AVAILABLE ? "[ ] " : "[X] ");
        cout << "\nGOLD       ";
        for (const auto& s : showSeats)
            if (s.getType() == SeatType::GOLD)
                cout << s.getNumber() << (s.getStatus() == SeatStatus::AVAILABLE ? "[ ] " : "[X] ");
        cout << "\nPLATINUM   ";
        for (const auto& s : showSeats)
            if (s.getType() == SeatType::PLATINUM)
                cout << s.getNumber() << (s.getStatus() == SeatStatus::AVAILABLE ? "[ ] " : "[X] ");
        cout << "\n([ ] = available, [X] = booked)\n";
    }
};
