#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUS_PRICE 20
#define MAX_STOPS 6
#define REF_ID "BUS123"


struct Price
 {
    int no;
    int dfs;
    char name[30];
};

struct Card
{
    char cardID[10];
    int balance;
};

struct BusTicket
{
    char busnumber[10];
    char from[30];
    char destination[30];
    float fare;
};


int calculateFare(int from, int to)
 {
    int distance = abs(to - from);
    return (BUS_PRICE + (distance * 5));
}


void processEntry(struct Card *card, int ticketPrice, struct BusTicket *ticket)
 {
    printf("Card ID: %s\n", card->cardID);
    if (card->balance >= ticketPrice)
        {
        card->balance -= ticketPrice;
        printf("Fare Deducted: %d\n", ticketPrice);
        printf("Remaining Balance: %d\n", card->balance);
        printf("Access Granted.\n");
        printHardCopyTicket(*ticket);
    }
     else
        {
        printf("Insufficient balance. Do you want to recharge the card? (Y/N): ");
        char choice;
        scanf(" %c", &choice);
        if (choice == 'Y' || choice == 'y')
            {
            printf("Enter the amount to be recharged: ");
            int amount;
            scanf("%d", &amount);
            card->balance += amount;
            printf("Card Balance: %d\n", card->balance);
        }
    }
}


int processUPIPayment(int fare, struct BusTicket *ticket)
 {
    char enteredRefID[10];
    printf("Processing UPI payment of %d...\n", fare);
    printf("Payment successful! Reference ID: %s\n", REF_ID);
    printf("Enter Reference ID to confirm payment: ");
    scanf("%9s", enteredRefID);
    if (strcmp(REF_ID, enteredRefID) == 0)
        {
        printf("Payment verified successfully!\n");
        printHardCopyTicket(*ticket);
        return 1;
    }
     else
        {
        printf("Payment failed! Invalid Reference ID.\n");
        return 0;
    }
}

int cashPaymentMachine(float amount)
 {
    float paidAmount = 0;
    printf("Please insert cash into the machine. Required amount: %.2f\n", amount);

    while (paidAmount < amount)
        {
        float insertedCash;
        printf("Insert cash:");
        scanf("%f", &insertedCash);

        if (insertedCash <= 0)
            {
            printf("Invalid amount. Please insert a valid amount.\n");
            continue;
        }

        paidAmount += insertedCash;
        printf("Amount inserted:%.2f \n Remaining amount: %.2f\n", paidAmount, amount - paidAmount);
    }

    if (paidAmount > amount)
        {
        float change = paidAmount - amount;
        printf("Payment successful! Dispensing change: %.2f\n", change);
    }
    else
        {
        printf("Payment successful! No change required.\n");
    }

    return 1;
}


void printHardCopyTicket(struct BusTicket ticket)
 {
    printf("\n Printing Hard Copy Ticket\n");
    printf("Bus Number: %s\n",ticket.busnumber);
    printf("From: %s\n", ticket.from);
    printf("Destination: %s\n", ticket.destination);
    printf("Fare:%.2f\n", ticket.fare);
    printf("Ticket printed successfully! Please collect your ticket.\n");
}


void getBusDetails(struct BusTicket *ticket, struct Price busStops[], int from, int to) {
    printf("Enter the bus number: ");
    scanf("%s",ticket->busnumber);
    strcpy(ticket->from, busStops[from - 1].name);
    strcpy(ticket->destination, busStops[to - 1].name);
}

int main() {
    struct Price busStops[MAX_STOPS] = {
        {1, 0, "Mylavaram"}, {2, 2, "Venkatapuram"}, {3, 4, "Chavturu"},
        {4, 10, "Konduru"}, {5, 18, "Katubadipalem"}, {6, 20, "Kondapalli"}
    };
    struct Card userCards[] = {
        {"A12345", 100}, {"B67890", 10}, {"C54321", 50}
    };

    int from, to, ticketPrice, choice;
    char enteredCardID[10];
    struct BusTicket ticket;

    printf("Available Bus Stops:\n");
    for (int i = 0; i < MAX_STOPS; i++) {
        printf("%d. %s\n", busStops[i].no, busStops[i].name);
    }

    printf("\nEnter the from & to stop numbers: ");
    scanf("%d %d", &from, &to);
    ticketPrice = calculateFare(from, to);
    printf("Ticket cost: %d\n", ticketPrice);


    getBusDetails(&ticket, busStops, from, to);
    ticket.fare = ticketPrice;

    printf("\nChoose Payment Method:\n1. Card Payment\n2. UPI Payment\n3. Cash Payment\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("\nSwipe your card (Enter Card ID): ");
        scanf("%s", enteredCardID);
        int found = 0;
        for (int i = 0; i < 3; i++) {
            if (strcmp(enteredCardID, userCards[i].cardID) == 0) {
                found = 1;
                processEntry(&userCards[i], ticketPrice, &ticket);
                break;
            }
        }
        if (!found) {
            printf("Invalid Card. Access Denied.\n");
        }
    } else if (choice == 2) {
        if (processUPIPayment(ticketPrice, &ticket)) {
            printf("Bus fare paid successfully!\n");
        }
    } else if (choice == 3) {
        if (cashPaymentMachine(ticketPrice)) {
            printHardCopyTicket(ticket);
        }
    } else {
        printf("Invalid choice! Try again.\n");
    }

    return 0;
}

