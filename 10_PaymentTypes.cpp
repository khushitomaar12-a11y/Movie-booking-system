class UpiPayment : public Payment {
public:
    bool pay(double amount) override {
        int result;
        cout << "Processing UPI payment of Rs." << amount << "...\n";
        cout << "Enter 1 for successful payment, 0 for failed payment: ";
        cin >> result;
        return result == 1;
    }
    string getMethod() const override { return "UPI"; }
};

class CardPayment : public Payment {
public:
    bool pay(double amount) override {
        int result;
        cout << "Processing Card payment of Rs." << amount << "...\n";
        cout << "Enter 1 for successful payment, 0 for failed payment: ";
        cin >> result;
        return result == 1;
    }
    string getMethod() const override { return "CARD"; }
};

class CashPayment : public Payment {
public:
    bool pay(double amount) override {
        int result;
        cout << "Processing Cash payment of Rs." << amount << "...\n";
        cout << "Enter 1 for successful payment, 0 for failed payment: ";
        cin >> result;
        return result == 1;
    }
    string getMethod() const override { return "CASH"; }
};
