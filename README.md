# Symbol Table for Nested Scopes
Symbol Table records the variable names used in the source program along with its attributes.
Hash Tables (made using Array of linked lists to avoid collisions) are used to insert and find the variables in every symbol table of particular scope/level.
A new symbol table for every scope is Maintained and is linked with the surrounding scope.
Program is provided in a file. 
We read from the given file and implement the symbol table for the given program. 
Here input program is given in Pascal Language.

## Functionality

- **Initialize Scope**: When begin word is found in the file then function is called and Increments the current level and creates a new symbol table for that level. Links the new table to the previous level's table and updates the current level pointer used by lookup and insert functions.
- **assign**: When assign word is found in the file then function is called and Inserts the value of a variable in the current scope with the specified value.
- **print**: When print word is found in the file then function is called and Looks up the value of a variable in the current scope. If it does not exist in the current scope, looks it up in the surrounding scope.
- **Finalize Scope**: When end word is found in the file then function is called Changes the current level pointer so that it points to the table for the scope surrounding the current level.
