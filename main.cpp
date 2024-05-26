#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Person {
protected:
    string name;

public:
    void setName() {
        cout << "Enter Name: ";
        cin >> name;
    }

    virtual void displayDetails() {
        cout << "Name: " << name << endl;
    }
};

class Car {
private:
    int carID;
    string carType;
    string carModel;
    string carMake;
    int carYear;
    double carPrice;

public:
    void setDetails(int carID, string carType, string carModel, string carMake, int carYear, double carPrice) {
        this->carID = carID;
        this->carType = carType;
        this->carModel = carModel;
        this->carMake = carMake;
        this->carYear = carYear;
        this->carPrice = carPrice;
    }

    void displayInfo() {
        cout << "Car ID: " << carID << endl;
        cout << "Car Type: " << carType << endl;
        cout << "Car Model: " << carModel << endl;
        cout << "Car Make: " << carMake << endl;
        cout << "Car Year: " << carYear << endl;
        cout << "Car Price: " << carPrice << endl;
        cout << endl;
    }

    int getCarID() {
        return carID;
    }

    void readFromFile(ifstream &inFile) {
    char comma;
    inFile >> carID >> comma;
    getline(inFile, carType, ',');
    getline(inFile, carMake, ',');
    getline(inFile, carModel, ',');
    inFile >> carYear >> comma;
    inFile >> carPrice;
    inFile.ignore();
}

    void saveToFile(ofstream &outFile) {
        outFile << carID << "," << carType << "," << carMake << "," << carModel << "," << carYear << "," << carPrice << endl;
    }
};

class ShowRoom {
public:
    Car cars[20];
    int carCount;

public:
    ShowRoom() {
        carCount = 20;

        cars[0].setDetails(1000, "Sedan", "ModelX", "BrandY", 2022, 25000);
        cars[1].setDetails(1001, "SUV", "ModelA", "BrandZ", 2021, 30000);
        cars[2].setDetails(1002, "Coupe", "ModelB", "BrandX", 2020, 28000);
        cars[3].setDetails(1003, "Hatchback", "ModelC", "BrandW", 2019, 22000);
        cars[4].setDetails(1004, "Convertible", "ModelD", "BrandV", 2018, 35000);
        cars[5].setDetails(1005, "Sedan", "ModelE", "BrandU", 2022, 26000);
        cars[6].setDetails(1006, "SUV", "ModelF", "BrandT", 2021, 32000);
        cars[7].setDetails(1007, "Coupe", "ModelG", "BrandS", 2020, 29000);
        cars[8].setDetails(1008, "Hatchback", "ModelH", "BrandR", 2019, 23000);
        cars[9].setDetails(1009, "Convertible", "ModelI", "BrandQ", 2018, 36000);
        cars[10].setDetails(1010, "Sedan", "ModelJ", "BrandP", 2022, 27000);
        cars[11].setDetails(1011, "SUV", "ModelK", "BrandO", 2021, 33000);
        cars[12].setDetails(1012, "Coupe", "ModelL", "BrandN", 2020, 30000);
        cars[13].setDetails(1013, "Hatchback", "ModelM", "BrandM", 2019, 24000);
        cars[14].setDetails(1014, "Convertible", "ModelN", "BrandL", 2018, 37000);
        cars[15].setDetails(1015, "Sedan", "ModelO", "BrandK", 2022, 28000);
        cars[16].setDetails(1016, "SUV", "ModelP", "BrandJ", 2021, 34000);
        cars[17].setDetails(1017, "Coupe", "ModelQ", "BrandI", 2020, 31000);
        cars[18].setDetails(1018, "Hatchback", "ModelR", "BrandH", 2019, 25000);
        cars[19].setDetails(1019, "Convertible", "ModelS", "BrandG", 2018, 38000);
    }

    void loadCarsFromFile() {
        ifstream inFile("cars.csv");
        if (!inFile) {
            cerr << "Error: Unable to open file for reading cars." << endl;
            return;
        }

        while (inFile.peek() != EOF && carCount < 20) {
            cars[carCount].readFromFile(inFile);
            carCount++;
        }

        inFile.close();
    }

    void saveCarsToFile() {
        ofstream outFile("cars.csv");
        if (!outFile) {
            cerr << "Error: Unable to open file for saving cars." << endl;
            return;
        }

        for (int i = 0; i < carCount; i++) {
            cars[i].saveToFile(outFile);
        }

        outFile.close();
    }

    void addCar() {
        if (carCount >= 20) {
        	
            cout << "ShowRoom is full!! Cannot add more cars." << endl;
        
            return;
        }

        int carID = 1 + carCount;
        string carType, carModel, carMake;
        int carYear;
        double carPrice;
        cout << "Enter Car Type: ";
        cin >> carType;
        cout << "Enter Car Model: ";
        cin >> carModel;
        cout << "Enter Car Make: ";
        cin >> carMake;
        cout << "Enter Car Year: ";
        cin >> carYear;
        cout << "Enter Car Price: ";
        cin >> carPrice;
        cout << endl;

        cars[carCount].setDetails(carID, carType, carModel, carMake, carYear, carPrice);
        carCount++;
        cout<<"Car Added"<<endl;
    }

    void removeCar(int id) {
        int index = -1;

        for (int i = 0; i < carCount; ++i) {
            if (cars[i].getCarID() == id) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cerr << "Error: Car with ID " << id << " not found." << endl;
            return;
        }

        for (int i = index; i < carCount - 1; ++i) {
            cars[i] = cars[i + 1];
        }

        carCount--;
        cout << "Car with ID " << id << " removed successfully." << endl;
    }

    void displayShowroom() {
        cout << "Cars in Showroom:" << endl;
        for (int i = 0; i < carCount; i++) {
            cars[i].displayInfo();
            cout << "---------------------" << endl;
        }
    }

    int getCarByID(int id) {
        for (int i = 0; i < carCount; i++) {
            if (cars[i].getCarID() == id) {
                return i;
            }
        }

        return -1;  // Car not found
    }

    void giveFeedback() {
        string feedback;
        cout << "Enter your feedback: ";
        cin.ignore();
        getline(cin, feedback);
        cout<<endl;
    

        ofstream outFile("feedback.txt", ios::app);
        if (!outFile) {
            cerr << "Error: Unable to open file for saving feedback." << endl;
            return;
        }

        outFile << feedback << endl;
        outFile.close();
    }

    void displayFeedback() {
        ifstream inFile("feedback.txt");
        if (!inFile) {
            cerr << "Error: Unable to open file for reading feedback." << endl;
            return;
        }

        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }

        inFile.close();
    }
};

class Customer : public Person {
private:
    int customerID;

public:
    void setCustomerID() {
        cout << "Enter Customer ID: ";
        cin >> customerID;
    }

    void displayDetails() override {
        Person::displayDetails();
        cout << "Customer ID: " << customerID << endl;
        cout << endl;
    }

    void buyVehicle(ShowRoom &showroom, int id) {
        int carIndex = showroom.getCarByID(id);
        if (carIndex != -1) {
            Car &car = showroom.cars[carIndex];
            car.displayInfo();
            cout << "You have bought a vehicle" << endl;
            cout << endl;
        } else {
            cout << "Car not found." << endl;
        }
    }
void sellVehicle(ShowRoom &showroom) {
        try {
            showroom.addCar();
            showroom.saveCarsToFile();
            cout << "Vehicle added to showroom." << endl;
            cout << endl;
        } catch (...) {
            cerr << "An error occurred while selling vehicle "  << endl;
        }
    }
};

class Employee : public Person {
private:
    string employeeID;

public:
    void setEmployeeDetails() {
        cout << "Enter Employee ID: ";
        cin >> employeeID;
        setName();
    }

    void displayEmployeeDetails() {
        cout << "Employee ID: " << employeeID << endl;
        displayDetails();
    }

    bool validateEmployee(string username, string password) {
        return (username == "admin" && password == "password");
    }

    void addCarToShowroom(ShowRoom &showroom) {
        try {
            showroom.addCar();
            showroom.saveCarsToFile();
            
            cout << endl;
        } catch (...) {
            cerr << "An error occurred while adding car to showroom" << endl;
        }
    }

    void removeCarFromShowroom(ShowRoom &showroom) {
        try {
            int carID;
            cout << "Enter Car ID to remove: ";
            cin >> carID;
            showroom.removeCar(carID);
            showroom.saveCarsToFile();
            cout << "Car removed from showroom and file updated." << endl;
            cout << endl;
        } catch (...) {
            cerr << "An error occurred while removing car from showroom " << endl;
        }
    }

    void readCarsFromFile(ShowRoom &showroom) {
        showroom.loadCarsFromFile();
        cout << "Cars loaded from file successfully." << endl;
    }

    void saveCarsToFile(ShowRoom &showroom) {
        showroom.saveCarsToFile();
        cout << "Cars saved to file successfully." << endl;
    }
    
};

class Insurance 
{
    private:
        int CarID;
        string InsuranceProvider;
        string InsuranceType;
        string ExpiryDate;
        float PremiumAmount;
        Car InsuredCar;

    public:
        void setInsuranceDetails(int id, const Car& car) 
        {
            CarID = id;
            InsuredCar = car;
            cout << "Enter Insurance Provider: ";
            cin.ignore();
            getline(cin, InsuranceProvider);
            cout << "Enter Insurance Type (Comprehensive, Third-Party, etc.): ";
            getline(cin, InsuranceType);
            cout << "Enter Insurance Expiry Date (DD/MM/YYYY): ";
            getline(cin, ExpiryDate);
            cout << "Enter Premium Amount: ";
            cin >> PremiumAmount;
        }

        void displayInsuranceDetails()  
        {
            cout << endl << "Insurance Record for Vehicle ID: " << CarID << endl;
            cout << "Insurance Provider: " << InsuranceProvider << endl;
            cout << "Insurance Type: " << InsuranceType << endl;
            cout << "Insurance Expiry Date: " << ExpiryDate << endl;
            cout << "Premium Amount: " << PremiumAmount << endl;
            cout << "Insured Car Details:" << endl << endl;
            InsuredCar.displayInfo();
        }
};

int main() {
    ShowRoom showroom;
    Car car;
    int choice;

    do {
        cout << "------------Welcome to Car ShowRoom---------" << endl;
        cout << "1. Admin Portal" << endl;
        cout << "2. Customer Portal" << endl;
        cout << "3. Exit" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Employee employee;
                string username, password;
                cout << "Enter Username: ";
                cin >> username;
                cout << "Enter Password: ";
                cin >> password;
                if (employee.validateEmployee(username, password)) {
                    int adminChoice;
                    do {
                        cout << endl;
                        cout << "--------Welcome to Admin Menu-------- " << endl;
                        cout << "1. Add Car" << endl;
                        cout << "2. Remove Car" << endl;
                        cout << "3. Display Showroom" << endl;
                        cout << "4. Load Cars from File" << endl; // New option
                        cout << "5. Save Cars to File" << endl; // New option
                        cout << "6. Logout" << endl;
                        cout << endl;
                        cout << "Enter your choice: ";
                        cin >> adminChoice;

                        switch (adminChoice) {
                            case 1:
                                employee.addCarToShowroom(showroom);
                                break;
                            case 2:
                                employee.removeCarFromShowroom(showroom);
                                break;
                            case 3:
                                showroom.displayShowroom();
                                break;
                            case 4:
                                employee.readCarsFromFile(showroom); 
                                break;
                            case 5:
                                employee.saveCarsToFile(showroom); 
                                break;
                            case 6:
                                cout << "Logging out" << endl;
                                break;
                            default:
                                cout << "Invalid choice. Please try again" << endl;
                        }
                    } while (adminChoice != 6);
                } else {
                    cout << "Invalid credentials. Access denied." << endl;
                }
                break;
            }
            case 2: {
                Customer customer;
                customer.setName();
                customer.setCustomerID();
                int customerChoice;
                do {
                    cout << "-----------Welcome to Customer Menu---------" << endl;
                    cout << "1. Buy Vehicle" << endl;
                    cout << "2. Sell Vehicle" << endl;
                    cout << "3. Display Showroom" << endl;
                    cout << "4. Give Feedback" << endl;
                    cout << "5. Display Feedback" << endl;
                    cout << "6. Add Car Insurance" << endl;
                    cout << "7. Exit" << endl;
                    cout << "Enter your choice: ";
                    cin >> customerChoice;

                    switch (customerChoice) 
                    {
                        case 1: {
                            showroom.displayShowroom();
                            int carID;
                            cout << "Enter Vehicle ID to buy: ";
                            cin >> carID;
                            customer.buyVehicle(showroom, carID);
                            break;
                        }
                        case 2:
                            customer.sellVehicle(showroom);
                            break;
                        case 3:
                            showroom.displayShowroom();
                            break;
                        case 4:
                            showroom.giveFeedback();
                            break;
                        case 5:
                            showroom.displayFeedback();
                            break;
                        case 6:                         
                        {
                            showroom.displayShowroom();
                            int carID;
                            cout << "Enter Vehicle ID to insure: ";
                            cin >> carID;
                            int carIndex = showroom.getCarByID(carID);
                            if (carIndex != -1) {
                                Insurance insurance;
                                insurance.setInsuranceDetails(carID, showroom.cars[carIndex]); 
                                cout << "Insurance details added." << endl;
                                insurance.displayInsuranceDetails();
                            } else {
                                cout << "Car not found." << endl;
                            }
                            break;
                        }
                        case 7:
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                            break;

                    }
                } while (customerChoice != 7);
                break;
            }
            case 3:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}