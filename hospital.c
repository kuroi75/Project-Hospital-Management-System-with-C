#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_DOCTORS 10
#define ADMIN_PASSWORD "123"

// for doctor
struct Doctor
{
    int id;
    char name[50];
    char depart[50];
    float fee;
};

//for patient
struct patient
{
    int id;
    char name[50];
    int age;
    char gender[10];
    char type[20];
    int docID;
};

//global variable
struct Doctor doctors[MAX_DOCTORS];
struct patient patients[MAX_PATIENTS];
int doctor_Count = 0;
int patient_count = 0;

//all doctors
void allDoctors()
{
    //doctor 1
    strcpy(doctors[0].name, "Dr. Fahad");
    strcpy(doctors[0].depart, "General/Emergency");
    doctors[0].fee = 99; //bdt
    doctors[0].id = 101;

    //doctor 2
    strcpy(doctors[1].name, "Dr. Tirtha");
    strcpy(doctors[1].depart, "Neurology");
    doctors[1].fee = 800; //bdt
    doctors[1].id = 102;

    //doctor 3
    strcpy(doctors[2].name, "Dr. Riad");
    strcpy(doctors[2].depart, "General");
    doctors[2].fee = 500; //bdt;
    doctors[2].id = 103;


    //doctor 4
    strcpy(doctors[3].name, "Dr. Lamia");
    strcpy(doctors[3].depart, "Gynecologist");
    doctors[3].fee = 500; //bdt
    doctors[3].id = 104;

    //doctor 5
    strcpy(doctors[4].name, "Dr. Monawar");
    strcpy(doctors[4].depart, "Cardiology");
    doctors[4].fee = 600; //bdt
    doctors[4].id = 105;

    doctor_Count = 5;
}
// few demo patients
void loadDemoP()
{
    //patient 1
    strcpy(patients[0].name, "Jabir");
    patients[0].age = 21;
    strcpy(patients[0].gender, "male");
    strcpy(patients[0].type, "Regular");
    patients[0].docID = 105;
    patients[0].id = 1;

    //patient 2
    strcpy(patients[1].name, "Fahim");
    patients[1].age = 21;
    strcpy(patients[1].gender, "male");
    strcpy(patients[1].type, "Regular");
    patients[1].docID = 102;
    patients[1].id = 2;

    //patient 2
    strcpy(patients[2].name, "Rafi");
    patients[2].age = 20;
    strcpy(patients[2].gender, "male");
    strcpy(patients[2].type, "Emergency");
    patients[2].docID = 101;
    patients[2].id = 2;

    patient_count =3;
}

// all patients
void allPatient()
{
    if (patient_count >= MAX_PATIENTS)
    {
        printf("Hospital is FULL!\nPlease contact authority if emergency.\n");
        return;
    }
    struct patient p;
    p.id = patient_count + 1;

    printf("Enter your name: ");
    //scanf("%s", p.name);
    scanf(" %[^\n]", p.name); //for full name with spasc

    printf("\nEnter age: ");
    scanf("%d", &p.age);

    printf("\nEnter gender: ");
    scanf("%s",p.gender);

    int choice;
    printf("Choose appointment type:\n");
    printf("1. Emrgency! \n2. Regular\n");
    scanf("%d", &choice);


    if(choice==1) //in emergency send to 1st doc
    {
        strcpy(p.type,"Emergency");
        p.docID = doctors[0].id;
        printf("\nAssigned to %s (Emergency). Fee: %.2f BDT\n", doctors[0].name, doctors[0].fee);

    }
    else
    {
        strcpy(p.type, "Regular");
        printf("Available doctors: \n");
        for(int i =0; i < doctor_Count; i++)
        {
            printf("%d. %s - %s - Fee: %.2f BDT - (ID: %d)\n", i + 1, doctors[i].name, doctors[i].depart, doctors[i].fee, doctors[i].id);
        }
        int docChoice;
        printf("select doctor (1-%d): ", doctor_Count);
        scanf("%d", &docChoice);
        if(docChoice >= 1&& docChoice <= doctor_Count)
        {
            p.docID = doctors[docChoice - 1].id;
            printf("\nAssigned to %s. \n", doctors[docChoice - 1].name);
        }else
        {
            printf("Invalid doctor selected. Auto assigning to General doctor.\n");
            p.docID = doctors[2].id;
        }
    }

    patients[patient_count] =p;
    patient_count++;
    printf("registered successfully \n");
}

//Admin panel
void adminPanel()
{
    int adminChoice;
    while (1)
    {
        printf("\n=======================");
        printf("\n||--- Admin Panel ---||\n");
        printf("=======================\n");
        printf("1. Show All Patients\n");
        printf("2. Search Patient\n");
        printf("3. View Stats\n");
        printf("4. Discharge Patient\n");
        printf("5. Show Patients by Doctor\n");
        printf("6. Exit Admin Panel\n");
        printf("Enter your choice: ");
        scanf("%d", &adminChoice);

        switch (adminChoice)
        {
            case 1:
                showPatients();
                break;

            case 2:
                searchPatient();
                break;

            case 3:
                printf("Total doctors: %d\n", doctor_Count);
                printf("Total patients: %d\n", patient_count);
                break;

            case 4:
                deletePatient();
                break;

            case 5:
                showPatientsBydoctor();
                break;

            case 6:
                return;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

int verifyAdmin()
{
    char input[50];
    printf("Enter admin password: ");
    scanf("%s", input);


    if (strcmp(input, ADMIN_PASSWORD) == 0) {
        return 1;
    }else
    {
        printf("Incorrect password! \n");
        return 0;
    }
}

// main face (show)
int main()
{
    //load doctors and demo patients
    allDoctors();
    loadDemoP();

    int choice;
    while (1)
    {
        printf("\n======================================");
        printf("\n||--- Hospital Management System ---||");
        printf("\n======================================\n");

        printf("1. New Patient\n");
        printf("2. Admin Panel\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
        allPatient();
        }else if (choice == 2)
        {
            if (verifyAdmin()) {
                adminPanel();
        }
        }else if (choice == 3) {
            printf("Exiting system...\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}


//search patient and list
void showPatients()
{
    if(patient_count == 0)
    {
        printf("ZERO patients.\n");
        return;
    }
    printf("\n--- Patient list ---\n");
    for(int i= 0; i<patient_count;i++)
    {
        printf("ID: %d\n", patients[i].id);
        printf("Name: %s\n", patients[i].name);
        printf("Age: %d\n", patients[i].age);
        printf("Gender: %s\n", patients[i].gender);
        printf("Type: %s\n", patients[i].type);
        printf("Assigned Doctor ID: %d\n", patients[i].docID);
        printf("----------------------\n");
    }
}

void searchPatient()
{
    if (patient_count == 0)
    {
        printf("ZERO patients");
        return;
    }

    char name[50];
    printf("Search by Name: ");
    scanf(" %[^\n]", name);
    for (int i = 0; i < patient_count; i++) {
        if (strcmp(patients[i].name, name) == 0)
        {
            printf("Patient Found:\nID: %d\nAge: %d\nGender: %s\nType: %s\nAssigned Doctor ID: %d\n",
                       patients[i].id, patients[i].age, patients[i].gender, patients[i].type, patients[i].docID);
        return;
        }
    }
        printf("No patient found with name %s.\n", name);
}

//show patients using POINTER
void showPatientsBydoctor()
{
    int docID;
    printf("enter Doctor ID: ");
    scanf("%d", &docID);

    int found = 0;
    printf("\n -- Patients under doctor ID: %d -- \n", docID);
    for(int i = 0; i<patient_count; i++)
    {
        if(patients[i].docID == docID)
        {
            printf("Patient ID: %d\n", patients[i].id);
            printf("Name: %s\n", patients[i].name);
            printf("Age: %d\n", patients[i].age);
            printf("Gender: %s\n", patients[i].gender);
            printf("Type: %s\n", patients[i].type);
            printf("\n");
            found= 1;
        }
    }
        if (!found)
    {
        printf("No patients is under this doctor\n");
    }
}

//delete patient
void deletePatient()
{
    int id;
    printf("Enter patient ID to discharge: ");
    scanf("%d", &id);

    int found =0;
    int i,j;
    for (i =0; i< patient_count; i++)
    if(patients[i].id == id)
    {
        found = 1;
        for(j= i; j< patient_count - 1; j++)
        {
            patients[j]= patients[j+1];
            patients[j].id--;
        }
        patient_count--;
        printf("patient ID %d discharged \n", id);
    }
     if (!found)
        printf("No patient found with ID %d.\n", id);
}
