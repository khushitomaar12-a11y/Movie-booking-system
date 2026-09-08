enum class SeatType { SILVER, GOLD, PLATINUM };

class Seat {
private:
    string number;
    SeatType type;

public:
    Seat(string number, SeatType type) : number(number), type(type) {}

    string getNumber() const { return number; }
    SeatType getType() const { return type; }

    static string typeName(SeatType type) {
        if (type == SeatType::SILVER) return "SILVER";
        if (type == SeatType::GOLD) return "GOLD";
        return "PLATINUM";
    }

    static double price(SeatType type) {
        if (type == SeatType::SILVER) return 150;
        if (type == SeatType::GOLD) return 250;
        return 400;
    }
};
