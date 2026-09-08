class PriceCalculator {
public:
    double calculate(const vector<ShowSeat*>& seats) const {
        double total = 0;
        for (ShowSeat* seat : seats)
            total += seat->getPrice();
        return total;
    }
};
