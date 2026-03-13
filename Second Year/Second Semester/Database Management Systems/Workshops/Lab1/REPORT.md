# REPORT
## Design decisions
- Project the application using **Layered Architecture**
- Create **DatabaseManager** to manage the database connection

## Problems found and solutions
- Problem: Reused code for the database connection
- Solution: Create a new class for the database connection
- Problem: Create only one repository interface for all repositories
- Solution: Create a new interface for each repository
- Problem: Parsing the exact type of variables in the service to create objects, which was rigid and hard to extend
- Solution: Use DTOs (Data Transfer Objects) to carry data from the UI to the service, making the system more flexible and extensible, as new fields can be added without changing the service method signatures
- Problem: Ensuring data correctness from the UI to the service
- Solution: Validate types and formats in the UI and validating the business logic in the service

## What I learned
- Better understanding of the database connection process
- Better understanding of the layered architecture
- Better understanding of how to use interfaces
- Better understanding of how to use DTOs