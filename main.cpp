#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

#include "01_Movie.cpp"
#include "02_Seat.cpp"
#include "03_Screen.cpp"
#include "04_Cinema.cpp"
#include "06_ShowSeat.cpp"
#include "05_Show.cpp"
#include "07_Customer.cpp"
#include "08_Booking.cpp"
#include "09_Payment.cpp"
#include "10_PaymentTypes.cpp"
#include "11_PriceCalculator.cpp"
#include "12_TicketPrinter.cpp"
#include "13_BookingService.cpp"

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    Cinema cinema("PVR Demo Cinema");

    Movie movie1("3 Idiots", "Hindi", 170);
    Movie movie2("Interstellar", "English", 169);
    vector<Movie*> movies = {&movie1, &movie2};

    vector<Show> shows;
    shows.emplace_back(&movie1, &cinema.getScreens()[0], "06:00 PM");
    shows.emplace_back(&movie1, &cinema.getScreens()[1], "09:00 PM");
    shows.emplace_back(&movie2, &cinema.getScreens()[0], "07:00 PM");

    Customer customer("Lucky", "9876543210");
    BookingService bookingService;

    while (true) {
        cout << "\n===== MOVIE TICKET BOOKING =====\n";
        cout << "1. Movies  2. Book  3. Cancel  4. My tickets  0. Exit\n";
        cout << "Choose: ";

        int choice;
        if (!(cin >> choice)) {
            clearInput();
            cout << "Invalid menu choice.\n";
            continue;
        }

        if (choice == 0) break;

        if (choice == 1) {
            cout << "\nMovies currently playing:\n";
            for (size_t i = 0; i < movies.size(); ++i)
                cout << "[" << i + 1 << "] " << movies[i]->getTitle()
                     << " | " << movies[i]->getLanguage()
                     << " | " << movies[i]->getDuration() << " min\n";

            int movieChoice;
            cout << "Choose movie: ";
            cin >> movieChoice;
            if (!cin || movieChoice < 1 || movieChoice > (int)movies.size()) {
                clearInput();
                cout << "Invalid movie choice.\n";
                continue;
            }

            Movie* selectedMovie = movies[movieChoice - 1];
            cout << "Shows for " << selectedMovie->getTitle() << ":\n";
            for (size_t i = 0; i < shows.size(); ++i)
                if (shows[i].getMovie() == selectedMovie)
                    cout << "Show " << i + 1 << " | Screen-" 
                         << shows[i].getScreen()->getScreenNumber()
                         << " | " << shows[i].getStartTime() << "\n";
        }
        else if (choice == 2) {
            cout << "\nMovies currently playing:\n";
            for (size_t i = 0; i < movies.size(); ++i)
                cout << "[" << i + 1 << "] " << movies[i]->getTitle() << "\n";

            int movieChoice;
            cout << "Choose movie: ";
            cin >> movieChoice;
            if (!cin || movieChoice < 1 || movieChoice > (int)movies.size()) {
                clearInput();
                cout << "Invalid movie choice.\n";
                continue;
            }

            Movie* selectedMovie = movies[movieChoice - 1];
            vector<int> showIndexes;
            cout << "\nShows:\n";
            for (size_t i = 0; i < shows.size(); ++i) {
                if (shows[i].getMovie() == selectedMovie) {
                    showIndexes.push_back((int)i);
                    cout << showIndexes.size() << ". Screen-"
                         << shows[i].getScreen()->getScreenNumber()
                         << " | " << shows[i].getStartTime() << "\n";
                }
            }

            int showChoice;
            cout << "Choose show: ";
            cin >> showChoice;
            if (!cin || showChoice < 1 || showChoice > (int)showIndexes.size()) {
                clearInput();
                cout << "Invalid show choice.\n";
                continue;
            }

            Show& selectedShow = shows[showIndexes[showChoice - 1]];
            selectedShow.displaySeats();

            cout << "Enter number of seats: ";
            int seatCount;
            cin >> seatCount;
            if (!cin || seatCount < 1 || seatCount > 10) {
                clearInput();
                cout << "Invalid seat count.\n";
                continue;
            }

            vector<string> seatNumbers;
            for (int i = 0; i < seatCount; ++i) {
                string number;
                cout << "Enter seat " << i + 1 << ": ";
                cin >> number;
                seatNumbers.push_back(number);
            }

            cout << "Pay by: 1.UPI  2.Card  3.Cash\nChoose: ";
            int paymentChoice;
            cin >> paymentChoice;

            bookingService.bookTicket(&customer, &selectedShow, seatNumbers, paymentChoice);
        }
        else if (choice == 3) {
            string bookingId;
            cout << "Enter booking ID: ";
            cin >> bookingId;
            bookingService.cancelBooking(bookingId);
        }
        else if (choice == 4) {
            bookingService.printMyTickets(&customer);
        }
        else {
            cout << "Invalid menu choice.\n";
        }
    }

    cout << "Thank you!\n";
    return 0;
}
