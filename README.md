# Dungeon Adventure Game

This is a text-based adventure game where the player explores different rooms, fights monsters, collects items, and heals themselves. The goal of the game is for the player to survive, defeat the monsters, and complete the adventure. The game uses a simple command-line interface and is written in the C programming language.

---

## Features

- **Start the Game**: The player, rooms, monsters, and items are created with the help of structs and initialized with their starting values.
- **Handle Command**:  A command menu is written where the user input is taken and the desired action is performed.
- **Move Player**: The player can move between rooms connected via the `initGame` method, with directions like right, left, up, down..
- **Look Room**: The player can look into the room to see which items and monsters are present using the `lookRoom` method. The next move can be adjusted based on the look method's output.
- **Collecting Items**: The player can collect items in the room. These items can include health potions, weapons, and other useful objects.
- **Attack Monsters**: The player can attack monsters in the room. Weapons or bare hands can be used for attacks.
- **Heal the Player**: The player can use health items from their inventory to heal their health points.
- **Inventory System**: The player can carry a limited number of items. These items can be used for attack, defense, or healing. Additionally, the player can list the items added to their inventory.
- **Save and Load the Game**: The player’s progress can be saved to a file and later loaded to continue from where they left off.
- **Win and Lose Conditions**:The player wins by defeating all the monsters in the game. The game is lost if the player’s health points drop to zero.

---

## Start the Game

### Start the Game:
** `initGame` Method**  
Prepares the basic setup of the game world and starting conditions. This method creates the rooms, defines the connections between rooms, places monsters and items, and sets the player's starting room and status.

- **What Does It Do?**
   -Creates rooms and connects them.
   -Places monsters and items randomly in the rooms.
   -Sets the player’s starting conditions (health, inventory, starting room).
- **Key Points:**
  - Correct setup at the beginning of the game is crucial for proper gameplay.
  - Monsters and items are placed in different rooms each time, adding variety to the gameplay.

---

## HandleCommand

### Handling Commands:
** `handleCommand` Metodu**  
Processes the commands entered by the player during the game and triggers the appropriate actions. All in-game interactions are handled through this method.

- **What Does It Do?**
  - Analyzes the entered command (e.g., `move`, `pickup`, `attack`).
  - Calls the corresponding methods for each command (e.g., `movePlayer`, `pickupItem`, `lookRoom`).

- **Key Points:**
  -Commands must be defined correctly. Invalid commands are communicated to the player with a clear error message
  - All commands are checked within the `handleCommand` method through a conditional structure.


---
## Gameplay

###  Moving the Player:
**`movePlayer` Method**  
Allows the player to move between rooms. The valid directions for movement are checked and the player’s position is updated.

- **What Does It Do?**
  - Checks the player’s current room.
  - Determines if the desired direction is valid (e.g., "up", "down", "left", "right").
  - If the direction is valid, moves the player in that direction; otherwise, displays an error message to the player.

- **Key Points:**
  - Each room is connected to certain directions only. For example, there may be no room above a certain room.
  - Every time the player moves, the new room’s status (items and monsters) is checked.

---

## Look Room

### Looking into the Room:
**`lookRoom` Metodu**  
Allows the player to examine the current room. This method informs the player of the monsters and items present in the room.

- **What Does It Do?**
  - Lists the monsters (if any) in the room along with their statuses.
  - Lists the items present in the room.
 
- **Key Points:**
  - Providing detailed information about the room’s status is important for the player to strategize.
  - The monsters and items in the room influence the player’s next move.

---



### Collecting Items:
**`pickupItem` Method**
The player can collect useful items found in the rooms and add them to their inventory. These items are crucial for progressing or surviving in the game.  
- **What Does It Do?**
  - The player types the `pickupItem` command.
  - The room’s inventory is checked and the available items are listed.
  - The player selects an item to collect, and it is added to the player’s inventory.
  - If the inventory is full, a warning is displayed to the player.
- **Key Points:**
  - Items can be weapons, health potions, or quest items.
  -The player’s inventory is limited; strategic choices must be made.
  -Some items can only be collected after the room’s monsters are defeated.

---

### Attacking Monsters:
**`attackCreature` Method**
The player can attack the monsters present in the room to eliminate threats. Either items or bare hands can be used for attacks.
- **What Does It Do?**
  - The player types the `attackCreature` command.
  - The monster in the room is displayed on the screen.
  - The player selects the monster to attack and the item they want to use.
  -The attack power of the selected item reduces the monster’s health points. If the monster’s 
health points reach zero, it dies.

- **Key Points:**
   -Different items have different attack powers. For example, a sword does more damage than bare hands.
   -If the player’s attack power is low, monsters may kill the player. Choosing the right item is crucial.
  

---

### Healing the Player:
**`healPlayer` Method**
The player can use health items from their inventory to restore their health points. This is critical for the player’s survival.
- **What Does It Do?**
  - The player types the `healPlayer` command.
  - The available health items in the inventory are listed.
  -The player selects a health item to use.
  -After using the selected item, the player’s health points are restored and the item is removed from the inventory.silinir.
- **Key Points:*
   -Health items are limited and should be used carefully.
   -A maximum of two health items can be used after defeating a monster.
   -Healing can only be done if the health points are not already full.
   -If there are no health items, a warning message is displayed to the player.

---

### Inventory System:
**`displayInventory` Method**
All the items collected by the player are stored in the inventory. The inventory has a limited capacity, so the player can only carry a certain number of items.
- **What Does It Do?**
  - The player types the `displayInventory` command.
  - The names and types of the items in the inventory are displayed.
  -The player can use items from the inventory.
  -Health items are removed from the inventory when used, making space for more items.
- **Key Points:**
  -The inventory must be managed properly.
  -The player should not collect unnecessary items as only health items can be discarded from the inventory, while attack items cannot be discarded.
 

---

### Saving and Loading:
**`saveGame` Method**
**`loadGame` Method**
These methods allow the player to save their progress and continue from where they left off. This is especially useful for longer play sessions. 
- **What Does It Do?**
  -The player types the  `saveGame` command. The game state is saved to a file called  
 `savegame.dat`.
  - The player can later type the `loadGame`command to resume from where they left off.
- **Key Points:**
  - The player’s current room, inventory, and health status are saved.
  -The loading process restores the game state exactly as it was.
  -If the file cannot be found during loading, an error message is displayed to the player.


## Requirements
   -C Compiler (GCC or any other C compiler).
   -Terminal or command-line interface.

---

## Compilation


To compile the game, you can use the following commands:

If you're using Makefile to compile the game, you can simply run the following command:
 
   ```bash
   make
 ```

If you want to clear, this will remove all object files and the executable, allowing you to start fresh.

```bash
make clean
```

Alternatively, this command is used to compile a source file (Game.c) and generate an executable file (Game.exe) in C:
  ```bash
gcc -o Game.exe Game.c  
```






