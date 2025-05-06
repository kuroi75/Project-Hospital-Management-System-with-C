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


void allDoctors()
{
    //doctor 1
    strcpy(doctors[0].name, "Dr. Fahad");
    strcpy(doctors[0].depart, "General/Emergency");
    doctors[0].id = 101;

    //doctor 2
    strcpy(doctors[1].name, "Dr. Tirtha");
    strcpy(doctors[1].depart, "Neurology");
    doctors[1].id = 102;

    //doctor 3
    strcpy(doctors[2].name, "Dr. Jubair");
    strcpy(doctors[2].depart, "General");
    doctors[2].id = 103;


    //doctor 4
    strcpy(doctors[3].name, "Dr. Lamia");
    strcpy(doctors[3].depart, "Gynecologist");
    doctors[3].id = 104;

    //doctor 5
    strcpy(doctors[4].name, "Dr. Monowar");
    strcpy(doctors[4].depart, "Cardiology");
    doctors[4].id = 105;

    doctor_Count = 5;
}


void allPatient()
{
    if (patient_count >= MAX_PATIENTS)
    {
        printf("Hospital is FULL!\nPlease contact authority if emergency.\n");
        return 0;
    }
    struct patient p;
    p.id = patient_count + 1;

    printf("Enter your name: ");
    //scanf("%s", p.name);
    scanf(" %[^\n]", p.name);
    //for full name with spasc

    printf("\nEnter age: ");
    scanf("%d", &p.age);

    printf("\nEnter gender: ");
    scanf("%s",p.gender);

    int choice;
    printf("Choose appointment type:\n");
    printf("1. Emrgency! \n2. Regular\n");
    scanf("%d", &choice);

    //in emergency send to 1st doc
    if(choice==1)
    {
        strcpy(p.type,"Emergency");
        p.docID = doctors[0].id;
        printf("\nAssigned to %s (Emergency). \n",doctors[0].name);
    }
    else
    {
        strcpy(p.type, "Regular");
        printf("Available doctors: \n");
        for(int i =0; i < doctor_Count; i++)
        {
            printf("%d. %s - %s (ID: %d)\n", i + 1, doctors[i].name,doctors[i].depart,doctors[i].id);
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

//admin panel
void adminPanel()
{
    int adminChoice;
    while (1)
    {
        printf("\n--- Admin Panel ---\n");
        printf("1. Show All Patients\n");
        printf("2. Search Patient\n");
        printf("3. View Stats\n");
        printf("4. Exit Admin Panel\n");
        printf("Enter your choice: ");
        scanf("%d", &adminChoice);

        if (adminChoice == 1)
            {
                showPatients();
            }else if (adminChoice == 2)
            {
                searchPatient();
            }else if (adminChoice == 3)
            {
                printf("Total doctors: %d\n", doctor_Count);
                printf("Total patients: %d\n", patient_count);
            } else if (adminChoice == 4)
            {
                break;
            } else {
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
    allDoctors();
    int choice;
    while (1)
    {
        printf("\n--- Hospital Management System ---\n");
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
    printf("Search by Name \Enter: ");
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

