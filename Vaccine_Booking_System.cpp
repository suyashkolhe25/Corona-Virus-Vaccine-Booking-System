// Corona Vaccine Booking System

#include<iostream>
#include<conio.h>
#include<fstream>
#include<ctime>
#include<time.h>
using namespace std;

class Patient{
    private: 
        int patient_no = 0, date, month,  year;
        string patient_name, patient_address, contact_no_1,contact_no_2, aadhar_no_1, aadhar_no_2, aadhar_no_3;
    public:

         void createpatient(){

            cout<<"Enter Patient number: ";
            cin>>patient_no;
            cout<<"Enter name of patient: ";
            cin.ignore();
            getline(cin,patient_name);
            cout<<"Enter name of city/village in which patient resides: ";
            cin>>patient_address;
            cout<<"Enter contact number of patient (first 5 digits): ";
            cin>>contact_no_1;
            cout<<"Enter next 5 digits of number: ";
            cin>>contact_no_2;
            cout<<"Enter Aadhar number of patient (first 4 digits): ";
            cin>>aadhar_no_1;
            cout<<"Enter Aadhar number of patient (next 4 digits): ";
            cin>>aadhar_no_2;
            cout<<"Enter Aadhar number of patient (last 4 digits): ";
            cin>>aadhar_no_3;

            srand((unsigned)time(0));
            int a=rand()%5;
            time_t t = time(0);
            tm* tPtr = localtime(&t);
            date = (tPtr->tm_mday)+a;
            if (date>30){
                date %=30;
            }
            month = (tPtr->tm_mon)+1;
            year = (tPtr->tm_year)+1900;
            cout<<"Your appointment is fixed on: "<<date<<"/"<<month<<"/"<<year<<" at your nearest hospital";
        }

        void showpatient(){
            cout<<patient_no<<"  "<<patient_name<<"  "<<patient_address<<"  "<<contact_no_1<<contact_no_2<<"  "<<aadhar_no_1<<aadhar_no_2<<aadhar_no_3<<"  "<<date<<" "<<month<<endl;
        }

        void writePatient();
        void showAllPatient();
        void searchPatient(int t);
        void deletePatient(int t);
        void updatepatient(int t);
};

void Patient::writePatient(){
        ofstream fout;
        fout.open("Vaccine_appointment.txt", ios::app|ios::out);
        if(fout.is_open()){
            fout.write((char*)this, sizeof(*this));
            fout.close();
        }
        else{
            cout<<"Unable to open file...";
        }
}

void Patient::showAllPatient(){
    ifstream fin;
    fin.open("Vaccine_appointment.txt", ios::in);
    if (fin.is_open()){
        fin.read((char*)this, sizeof(*this));
        while (!(fin.eof())){
            showpatient();
            fin.read((char*)this, sizeof(*this));
        } 
        fin.close();
    }
    else
        cout<<"Unable to open file..."<<endl;
}

void Patient::searchPatient(int t){
    ifstream fin;
    int counter=0;
    fin.open("Vaccine_appointment.txt", ios::in);
    if (fin.is_open()){
        fin.read((char*)this, sizeof(*this));
        while (!(fin.eof())){
            if(t==patient_no){
                showpatient();
                ++counter;
            }
            fin.read((char*)this, sizeof(*this));
        }       
    }
    else {
        cout<<"Unable to open file...";
    }
        
    if (counter==0){
        cout<<"Record not found..."<<endl;
    }
    fin.close();
}

void Patient::deletePatient(int t){
    ifstream fin;
    ofstream fout;
    fin.open("Vaccine_appointment.txt", ios::in);
    if (fin.is_open()){
        fout.open("temp.txt", ios::out);
        fin.read((char*)this, sizeof(*this));
        while (!fin.eof()){
           if (!(t==patient_no)){
               fout.write((char*)this, sizeof(*this));
           }
           fin.read((char*)this, sizeof(*this));
        }  
        fin.close();
        fout.close();     
    }
    else{
        cout<<"Unable to open file...";
    }
    remove("Vaccine_appointment.txt");
    rename("temp.txt", "Vaccine_appointment.txt");
    cout<<"Record successfully deleted..."<<endl;
    cout<<"After deletion..."<<endl;
    showAllPatient();
}

void Patient::updatepatient(int t){
    fstream file;
    file.open("Vaccine_appointment.txt", ios::in|ios::out|ios::ate);
    file.seekg(0);
    file.read((char*)this, sizeof(*this));
    while (!file.eof()){
        if (t==patient_no){
            createpatient();
            int value = file.tellp();
            file.seekp(value-sizeof(*this));
            file.write((char*)this, sizeof(*this));
        }
        file.read((char*)this, sizeof(*this));
    }
    file.close();
}

void menu(){
    system("cls");
    cout<<"Welcome to Corona Vaccine Booking System"<<endl;
    cout<<"================================================="<<endl;
    cout<<"1. Create Patient record and book vaccine"<<endl;
    cout<<"2. Show all Vaccine booking record "<<endl;
    cout<<"3. Search for a specific booking record "<<endl;
    cout<<"4. Update a booking record"<<endl;
    cout<<"5. Delete a booking record"<<endl;
    cout<<"6. Exit"<<endl;
    cout<<"Enter your choice(1-6): "<<endl;
}

int main()
{
    Patient p;
    int n;
     while (1){    
    menu();
    char ch;
    cin>>ch;
    switch (ch)
    {
    case '1':  p.createpatient();
               p.writePatient();
               cout<<"\nNew record created..."<<endl;
               getch();
               break;
    case '2':  cout<<"\nDisplaying All records...."<<endl;
               p.showAllPatient();
               getch();
               break;
    case '3':  cout<<"\nEnter the patient number of the record to be searched: ";
               cin>>n;
               p.searchPatient(n);
               getch();
               break;
    case '4':  cout<<"\nEnter the patient number to be updated: ";
               cin>>n;
               p.updatepatient(n);
               getch();
               break;
    case '5':  cout<<"\nEnter the patient number whose record is to be deleted: ";
               cin>>n;
               p.deletePatient(n);
               cout<<"\nRecord Deleted...";
               getch();
               break;   
    case '6':  exit(0);
               break;
    default: cout<<"You have entered a wrong choice..."<<endl;
             break;
    }
    }
    
}