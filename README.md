# Banking System OOP Project
The project simulates some basic banking functionalities.

## User Roles
There are three type of roles in the app:
- Clients: can open, close and transfer bank accounts, check balance, redeem cheques
- Bankers: can approve, disapprove, validate tasks sent by customers
- Third-party employees: can send cheques with sum and codes to clients

Bankers work with three types of tasks:
- Open Account: sent by a user who wants to open a bank account
- Close Account: sent by a user who wants to close a bank account
- Change Bank: sent by a user who wants to move an account from one bank to another. Before being approved, the current bank must validate that such account exists.

## Functionalites:

### System:
- signup
- login [egn] [password]
- create_bank [bank_name]
- whoami
- help
- exit

### Client:
- check_avl [bank_name] [account_number]
- open [bank_name]
- close [bank_name] [account_number]
- redeem [bank_name] [account_number] [verification_code]
- change [new_bank_name] [current_bank_name] [account_number]
- list [bank_name]
- messages

### Banker:
- tasks
- view [task_idx]
- approve [task_idx]
- disapprove [task_idx] [message]
- validate [task_idx]
  
### Third-Party employeee:
- send_cheque [sum] [verification_code] [egn]
