# Flight Reservation Management System

## Overview
A console-based flight reservation management system implemented in C, allowing users to search flights, make reservations, cancel bookings, and manage passenger information.

## Features
- Flight Search: Find flights by departure city, arrival city, and date
- Ticket Reservation: Book flights for passengers
- Reservation Cancellation: Cancel existing flight reservations
- Passenger Information Management: Modify passenger details

## Data Structures
- `Avion`: Represents flight information (flight number, dates, price, times, aircraft, cities)
- `NodeArber`: Binary tree node for flight storage
- `Info`: Passenger information structure
- `NodeListe`: Linked list node for reservation management

## Key Functions
- `insertVol()`: Insert flights into binary search tree
- `rechercheVols()`: Search for available flights
- `Reserver_Billet()`: Book flight tickets
- `AnnulerRsrv()`: Cancel flight reservations
- `modifierInfoPassager()`: Update passenger information

## Getting Started
### Prerequisites
- C compiler (gcc recommended)
- Standard C libraries

### Compilation
```bash
gcc -o flight_reservation flight.c
./flight_reservation
```

## Usage
1. Select options from the main menu
2. Search flights by departure/arrival cities and date
3. Reserve tickets by entering passenger details
4. Cancel reservations using reservation number
5. Modify passenger information as needed

## Limitations
- In-memory storage (data is not persistent)
- Basic error handling
- Console-based interface

## Future Improvements
- Database integration
- Enhanced error handling
- Graphical user interface
- Seat selection
- Payment processing

## License
Open-source project
