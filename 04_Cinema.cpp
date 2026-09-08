class Cinema {
private:
    string name;
    vector<Screen> screens;

public:
    Cinema(string name) : name(name) {
        // Composition: Cinema creates and owns its Screen objects.
        screens.emplace_back(1);
        screens.emplace_back(2);
    }

    string getName() const { return name; }
    vector<Screen>& getScreens() { return screens; }
};
