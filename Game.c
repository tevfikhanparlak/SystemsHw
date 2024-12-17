 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_INVENTORY 4        //seting some limitations of the game
#define MAX_NAME_LEN 60
#define MAX_ITEMS_PER_ROOM 2
#define MAX_RECOVERY 2
typedef struct Item                  //item struct and some properties
{
    char itemName[MAX_NAME_LEN];
    int itemStrength;
    int itemHealth;
} Item;

typedef struct Creature              //creature struct and some properties
{
    char creatureName[MAX_NAME_LEN];
    int creatureHealth;
    int creatureStrength;
} Creature;

typedef struct Room                   //room struct and some properties
{
    int roomId;
    char roomDescription[250];
    struct Room *roomUp, *roomDown, *roomLeft, *roomRight;
    Item *roomItems[MAX_ITEMS_PER_ROOM];
    int roomItemCount;
    Creature *roomCreature;
} Room;

typedef struct Player              //player struct and some properties
{
    int playerHealth;
    int playerStrength;
    int playerNumberOfKills;
    int playerRecoveryCount;
    Item *playerInventory[MAX_INVENTORY];
    int playerInventoryCount;
    Room *playerCurrentRoom;
} Player;

// function and their prototypes
void initGame(Player *player, Room *rooms);
void handleCommand(Player *player, Room *rooms);
void movePlayer(Player *player, const char *direction);
void lookRoom(Player *player);
void pickupItem(Player *player, const char *itemName);
void attackCreature(Player *player);
void displayInventory(Player *player);
void healPlayer(Player *player);
void saveGame(Player *player, Room *rooms);
bool loadGame(Player *player, Room *rooms);

int main()
{
    Player player;                           // declare player
    Room *rooms = malloc(6 * sizeof(Room));  // Allocate memory using malloc for 6 rooms

    initGame(&player, rooms);               //calling init metot
    char loadChoice[4];
    printf("Do you want to load a saved game? (yes/no): ");   // it is about save load methods
    scanf("%s", loadChoice);

    if (strcmp(loadChoice, "yes") == 0)
    {
        if (!loadGame(&player, rooms))
        {
            printf("Starting a new game instead.\n");
        }
    }
    else
    {
        printf("Starting a new game.\n");
    }

    printf("Welcome to the Dungeon Adventure Game!\n");
    printf("Type commands like 'move <direction>', 'look', 'pickup <item>', 'attack', 'recover', 'inventory', 'save', 'load', or 'exit'.\n"); //game commands

    while (1)           //this game will loop in this method
    {
        handleCommand(&player, rooms);
    }

    // free resources for recover memory
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < rooms[i].roomItemCount; j++)
        {
            free(rooms[i].roomItems[j]);
        }
        if (rooms[i].roomCreature)
            free(rooms[i].roomCreature);
    }
    free(rooms);

    return 0;
}

void initGame(Player *player, Room *rooms)     //ths method provides to initialize game with some rooms and related with some items. Also include player and creature
{
    // initialize room with descriptions
    strcpy(rooms[0].roomDescription, "A room full of cold stone walls and echoing distant whispers.");
    strcpy(rooms[1].roomDescription, "A room with blood-stained walls and the floor with remnants of ancient rituals.");
    strcpy(rooms[2].roomDescription, "A room full of old grass, the smell of old grass in the air.");
    strcpy(rooms[3].roomDescription, "A misty garden full of withered, stunted trees and strange, withered flowers.");
    strcpy(rooms[4].roomDescription, "A damp, underground warm room with water dripping from the ceiling.");
    strcpy(rooms[5].roomDescription, "A large place filled with high columns, a room in which the disturbing sound of water and insects echoes in the silence.");

    for (int i = 0; i < 6; i++)
    {
        rooms[i].roomId = i;  //  initialize rooms with an id
    }

    // set up room connections
    rooms[0].roomUp = &rooms[1];
    rooms[0].roomDown = &rooms[3];
    rooms[0].roomLeft = &rooms[4];
    rooms[0].roomRight = &rooms[2];

    rooms[1].roomUp = NULL;
    rooms[1].roomDown = &rooms[0];
    rooms[1].roomLeft = NULL;
    rooms[1].roomRight = NULL;

    rooms[2].roomUp = NULL;
    rooms[2].roomDown = &rooms[5];
    rooms[2].roomLeft = &rooms[0];
    rooms[2].roomRight = NULL;

    rooms[3].roomUp = &rooms[0];
    rooms[3].roomDown = NULL;
    rooms[3].roomLeft = NULL;
    rooms[3].roomRight = &rooms[5];

    rooms[4].roomUp = NULL;
    rooms[4].roomDown = NULL;
    rooms[4].roomLeft = NULL;
    rooms[4].roomRight = &rooms[0];

    rooms[5].roomUp = &rooms[2];
    rooms[5].roomDown = NULL;
    rooms[5].roomLeft = &rooms[3];
    rooms[5].roomRight = NULL;

    for (int i = 0; i < 6; i++)
    {
        rooms[i].roomCreature = NULL;
    }

    // adding items into the rooms
    // maximum item numbers for each room is 2
    rooms[0].roomItemCount = 1;
    rooms[0].roomItems[0] = malloc(sizeof(Item));
    strcpy(rooms[0].roomItems[0]->itemName, "potion");
    rooms[0].roomItems[0]->itemStrength = 0;
    rooms[0].roomItems[0]->itemHealth = 40;

    //--------------------------------------------------
    rooms[1].roomItemCount = 2;
    rooms[1].roomItems[0] = malloc(sizeof(Item));
    strcpy(rooms[1].roomItems[0]->itemName, "dungeon water");
    rooms[1].roomItems[0]->itemStrength = 0;
    rooms[1].roomItems[0]->itemHealth = 50;
    rooms[1].roomItems[1] = malloc(sizeof(Item));
    strcpy(rooms[1].roomItems[1]->itemName, "stone");
    rooms[1].roomItems[1]->itemStrength = 40;
    rooms[1].roomItems[1]->itemHealth = 0;
    //-------------------------------------------------
    rooms[2].roomItemCount = 1;
    rooms[2].roomItems[0] = malloc(sizeof(Item));
    strcpy(rooms[2].roomItems[0]->itemName, "zulfikar sword");
    rooms[2].roomItems[0]->itemStrength = 80;
    rooms[2].roomItems[0]->itemHealth = 0;

    rooms[2].roomCreature = malloc(sizeof(Creature));
    strcpy(rooms[2].roomCreature->creatureName, "Middle level creature");
    rooms[2].roomCreature->creatureHealth = 150;
    rooms[2].roomCreature->creatureStrength = 25;
    //-----------------------------------------
    rooms[3].roomItemCount = 0;
    rooms[3].roomCreature = malloc(sizeof(Creature));
    strcpy(rooms[3].roomCreature->creatureName, "Dungeon Boss");
    rooms[3].roomCreature->creatureHealth = 200;
    rooms[3].roomCreature->creatureStrength = 40;
    //------------------------------------------------
    rooms[4].roomItemCount = 1;
    rooms[4].roomItems[0] = malloc(sizeof(Item));
    strcpy(rooms[4].roomItems[0]->itemName, "medicinal herb");
    rooms[4].roomItems[0]->itemStrength = 0;
    rooms[4].roomItems[0]->itemHealth = 25;
    rooms[4].roomCreature = malloc(sizeof(Creature));
    strcpy(rooms[4].roomCreature->creatureName, "Easy levet creature");
    rooms[4].roomCreature->creatureHealth = 100;
    rooms[4].roomCreature->creatureStrength = 10;
    //--------------------------------------------
    rooms[5].roomItemCount = 2;
    rooms[5].roomItems[0] = malloc(sizeof(Item));
    strcpy(rooms[5].roomItems[0]->itemName, "stick");
    rooms[5].roomItems[0]->itemStrength = 12;
    rooms[5].roomItems[0]->itemHealth = 0;
    rooms[5].roomItems[1] = malloc(sizeof(Item));
    strcpy(rooms[5].roomItems[1]->itemName, "golden apple");
    rooms[5].roomItems[1]->itemStrength = 0;
    rooms[5].roomItems[1]->itemHealth = 21;

    // initialize player
    player->playerHealth = 100;
    player->playerStrength = 5;
    player->playerNumberOfKills = 0;
    player->playerInventoryCount = 0;
    player->playerCurrentRoom = &rooms[0];
    player->playerRecoveryCount = 0;
}
void handleCommand(Player *player, Room *rooms)      
{
    char command[100], action[10], arg[90];         // arg should be larger
    printf("\n> ");
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = 0;           // remove new line character

    // parsing the commend 
    char *token = strtok(command, " ");           //take first word
    if (token != NULL)
    {
        strcpy(action, token);              
    }

    // reprocess with strtok to get the remaining part
    token = strtok(NULL, "");      // get all remaining part which belongs to args
    if (token != NULL)
    {
        strcpy(arg, token);        // extract arg
    }

    // commendt process
    if (strcmp(action, "move") == 0)
    {
        movePlayer(player, arg);   
    }
    else if (strcmp(action, "look") == 0)
    {
        lookRoom(player);
    }
    else if (strcmp(action, "pickup") == 0)
    {
        pickupItem(player, arg);  
    }
    else if (strcmp(action, "attack") == 0)
    {
        attackCreature(player);
    }
    else if (strcmp(action, "inventory") == 0)
    {
        displayInventory(player);
    }
    else if (strcmp(action, "recover") == 0)
    {
        healPlayer(player);
    }
    else if (strcmp(action, "save") == 0)
    {
        saveGame(player, rooms);
    }
    else if (strcmp(action, "load") == 0)
    {
        loadGame(player, rooms);
    }
    else if (strcmp(action, "exit") == 0)
    {
        printf("Exiting the game. Goodbye!\n");
        exit(0);
    }
    else
    {
        printf("Unknown command: %s\n", command);
    }
}

void movePlayer(Player *player, const char *direction) //move method provides to move with connected rooms which is initialized before
{
    Room *nextRoom = NULL;

    if (strcmp(direction, "up") == 0)
    {
        nextRoom = player->playerCurrentRoom->roomUp;
    }
    else if (strcmp(direction, "down") == 0)
    {
        nextRoom = player->playerCurrentRoom->roomDown;
    }
    else if (strcmp(direction, "left") == 0)
    {
        nextRoom = player->playerCurrentRoom->roomLeft;
    }
    else if (strcmp(direction, "right") == 0)
    {
        nextRoom = player->playerCurrentRoom->roomRight;
    }

    if (nextRoom)
    {
        player->playerCurrentRoom = nextRoom;
        printf("You moved %s.\n", direction);
    }
    else  //if there is not room
    {
        printf("You can't move %s from here.\n", direction);
    }
}

void lookRoom(Player *player) //we can see rooms with what there are inside
{
    printf("Room: %s\n", player->playerCurrentRoom->roomDescription);

    // if there are items, list
    if (player->playerCurrentRoom->roomItemCount > 0)
    {
        printf("Items in the room:\n");
        for (int i = 0; i < player->playerCurrentRoom->roomItemCount; i++)
        {
            printf("%d. %s\n", i + 1, player->playerCurrentRoom->roomItems[i]->itemName);

            // if item strengt >0 write
            if (player->playerCurrentRoom->roomItems[i]->itemStrength > 0)
            {
                printf("   Strength: %d\n", player->playerCurrentRoom->roomItems[i]->itemStrength);
            }

            // if item health >0 write
            if (player->playerCurrentRoom->roomItems[i]->itemHealth > 0)
            {
                printf("   Health: %d\n", player->playerCurrentRoom->roomItems[i]->itemHealth);
            }
        }
    }
    else
    {
        printf("There are no items here.\n");
    }

    // if there is creature show it
    if (player->playerCurrentRoom->roomCreature)
    {
        printf("A creature is here: %s (Health: %d)\n", player->playerCurrentRoom->roomCreature->creatureName,
               player->playerCurrentRoom->roomCreature->creatureHealth);
    }
}

void pickupItem(Player *player, const char *itemName)  //it provides to pickup items in rooms
{
    int found = 0;
    // general loop 
    for (int i = 0; i < player->playerCurrentRoom->roomItemCount; i++)
    {
        // compare to item name
        if (strcmp(player->playerCurrentRoom->roomItems[i]->itemName, itemName) == 0)
        {
            // if item found check it related with kill numbers
            if (strcmp(itemName, "zulfikar sword") == 0 && player->playerNumberOfKills < 2)
            {
                printf("You cannot pick up the Zulfikar Sword until you defeat 2 creatures.\n");
                return;
            }
            if (strcmp(itemName, "stone") == 0 && player->playerNumberOfKills < 1)
            {
                printf("You cannot pick up the knife until you defeat 1 creature.\n");
                return;
            }
            if (strcmp(itemName, "stick") == 0 && player->playerNumberOfKills > 0)
            {
                printf("You don't need the stick anymore.\n");
                return;
            }

            // control the number of inventory
            if (player->playerInventoryCount >= MAX_INVENTORY)
            {
                printf("Your inventory is full.\n");
                return;
            }

            player->playerInventory[player->playerInventoryCount++] = player->playerCurrentRoom->roomItems[i];
            printf("You picked up: %s\n", player->playerCurrentRoom->roomItems[i]->itemName);

            // remove item from the room
            for (int j = i; j < player->playerCurrentRoom->roomItemCount - 1; j++)
            {
                player->playerCurrentRoom->roomItems[j] = player->playerCurrentRoom->roomItems[j + 1];
            }
            player->playerCurrentRoom->roomItemCount--;
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("There is no item named '%s' in this room.\n", itemName);
    }
}

void attackCreature(Player *player) //method provides to attack creature at the end of this method player or creature should be killed.
{
    Creature *creature = player->playerCurrentRoom->roomCreature;

    if (!creature)   //if creature is not in the room
    {
        printf("There's no creature to attack here.\n");
        return;
    }

    printf("You attack the %s!\n", creature->creatureName);
    printf("You can select any of these items: \n");
    for (int i = 0; i < player->playerInventoryCount; i++)  //item selection
    {
        if (player->playerInventory[i]->itemStrength > 0)
        {
            printf("%d. %s (Strength: %d)\n", i + 1, player->playerInventory[i]->itemName, player->playerInventory[i]->itemStrength);
        }
    }

    printf("Enter the number of the item to use (or press 0 to attack with your bare hands): ");
    int choice;
    scanf("%d", &choice);
    getchar();           // cleaning '\n' character

    int attackStrength;

    if (choice == 0)             // player didn't choose an item player will attack with bare hands
    {
        attackStrength = player->playerStrength;
        printf("You attack with your bare hands! (Strength: %d)\n", attackStrength);
    }
    else if (choice > 0 && choice <= player->playerInventoryCount)  
    {
        Item *selectedItem = player->playerInventory[choice - 1];
        if (selectedItem->itemStrength > 0)
        {
            attackStrength = selectedItem->itemStrength;
            printf("You attack with %s! (Strength: %d)\n", selectedItem->itemName, attackStrength);
        }
        else
        {
            printf("That item has no strength. You attack with your bare hands instead! (Strength: %d)\n", player->playerStrength);
            attackStrength = player->playerStrength;
        }
    }
    else
    {
        printf("Invalid choice. You attack with your bare hands! (Strength: %d)\n", player->playerStrength);
        attackStrength = player->playerStrength;
    }

    // applying damages
    while (1)
    {
        // player attacks to the creature
        printf("Player attacked %s with %d damage.\n", creature->creatureName, attackStrength);
        creature->creatureHealth -= attackStrength;
        if (creature->creatureHealth > 0)
        {
            printf("Creature's health is: %d\n", creature->creatureHealth);
        }
        if (creature->creatureHealth <= 0)  //if died
        {
            printf("Congratulations! You defeated the %s!\n", creature->creatureName);
            free(creature);
            player->playerCurrentRoom->roomCreature = NULL;  // remove creature from the room
            player->playerNumberOfKills++;                   //increment kill numbers
            player->playerRecoveryCount = 0;                 //if creature die, recovery count becomes zero
            if (player->playerNumberOfKills == 3)           //win condition
            {
                printf("You killed all of the creatures. You WIN!!!\n");
                exit(0);             // end of the game if player kills all creatures
            }
            return; 
        }

        // creature attacks to player
        printf("%s attacked the player with %d damage.\n", creature->creatureName, creature->creatureStrength);
        player->playerHealth -= creature->creatureStrength;
        if (player->playerHealth > 0)
        {
            printf("Player's health is: %d\n", player->playerHealth);
        }

        if (player->playerHealth <= 0)
        {
            printf("You have been defeated. Game over.\n");
            exit(0);              // end of the game if player is defeated
        }
    }
}
   
void healPlayer(Player *player)           //method provides to increment player's health
{
    if (player->playerHealth >= 100)
    {
        printf("Your health is already full.\n");
        return;
    }

    if (player->playerRecoveryCount >= 2)     //each iteration olayer can use maximum 2 health item
    {
        printf("You have reached the maximum number of recoveries. You cannot heal anymore.\n");
        return;
    }

    int healthItemFound = 0;
    printf("Select a health item to use:\n");

    // list health items in player's inventory
    for (int i = 0; i < player->playerInventoryCount; i++)
    {
        if (player->playerInventory[i]->itemHealth > 0)   //if it is ealth item 
        {
            printf("%d. %s (Heals: %d)\n", i + 1, player->playerInventory[i]->itemName, player->playerInventory[i]->itemHealth);
            healthItemFound = 1;
        }
    }

    if (!healthItemFound)
    {
        printf("You have no health items in your inventory.\n");
        return;
    }

    printf("Enter the number of the health item to use: ");
    int choice;
    scanf("%d", &choice);
    getchar();    // clean '\n' character

    if (choice < 1 || choice > player->playerInventoryCount || player->playerInventory[choice - 1]->itemHealth <= 0)
    {
        printf("Invalid choice. Heal failed!\n");
        return;
    }

    Item *selectedItem = player->playerInventory[choice - 1];
    int healAmount = selectedItem->itemHealth;

    // add healamount to players health
    player->playerHealth += healAmount;
    if (player->playerHealth > 100)
    {
        player->playerHealth = 100;
    }

    printf("You used %s and restored %d health points. Current health: %d\n",
           selectedItem->itemName, healAmount, player->playerHealth);

    // remove used item from inventory
    for (int i = choice - 1; i < player->playerInventoryCount - 1; i++)
    {
        player->playerInventory[i] = player->playerInventory[i + 1];
    }
    player->playerInventoryCount--;   //the limit should be decrease
    player->playerRecoveryCount++;    //recovery count should be increase
    if (player->playerRecoveryCount >= 2)
    {
        printf("You cannot heal again until the next battle!\n");
    }
}

void displayInventory(Player *player)    //method provides to list inventory
{
    if (player->playerInventoryCount == 0)
    {
        printf("Your inventory is empty.\n");
        return;
    }

    printf("Your inventory:\n");
    for (int i = 0; i < player->playerInventoryCount; i++)
    {
        printf("- %s\n", player->playerInventory[i]->itemName);
    }
}

void saveGame(Player *player, Room *rooms)   //method provides to save current process into file
{
    FILE *file = fopen("savegame.dat", "w");
    if (!file)
    {
        printf("Failed to save the game.\n");
        return;
    }

    // saving player data
    fprintf(file, "%d\n", player->playerHealth);
    fprintf(file, "%d\n", player->playerStrength);
    fprintf(file, "%d\n", player->playerNumberOfKills);
    fprintf(file, "%d\n", player->playerRecoveryCount);
    fprintf(file, "%d\n", player->playerInventoryCount);

    // saving player's inventory
    for (int i = 0; i < player->playerInventoryCount; i++)
    {
        fprintf(file, "%s\n", player->playerInventory[i]->itemName);
        fprintf(file, "%d\n", player->playerInventory[i]->itemStrength);
        fprintf(file, "%d\n", player->playerInventory[i]->itemHealth);
    }

    // saving room datas
    for (int i = 0; i < 6; i++)
    {
        fprintf(file, "%d\n", rooms[i].roomId);
        fprintf(file, "%s\n", rooms[i].roomDescription);

        // saving room items
        fprintf(file, "%d\n", rooms[i].roomItemCount);
        for (int j = 0; j < rooms[i].roomItemCount; j++)
        {
            fprintf(file, "%s\n", rooms[i].roomItems[j]->itemName);
            fprintf(file, "%d\n", rooms[i].roomItems[j]->itemStrength);
            fprintf(file, "%d\n", rooms[i].roomItems[j]->itemHealth);
        }

        // saving room creature if it exist
        if (rooms[i].roomCreature)
        {
            fprintf(file, "1\n");       // creature represents with 1
            fprintf(file, "%s\n", rooms[i].roomCreature->creatureName);
            fprintf(file, "%d\n", rooms[i].roomCreature->creatureHealth);
            fprintf(file, "%d\n", rooms[i].roomCreature->creatureStrength);
        }
        else
        {
            fprintf(file, "0\n");     // if no creature represents with 0
        }
    }

    fclose(file);
    printf("Game saved successfully.\n");
}
bool loadGame(Player *player, Room *rooms)     //method provides to load data from file
{
    FILE *file = fopen("savegame.dat", "r");
    if (!file)
    {
        printf("Failed to load the game.\n");
        return false;
    }

    // looading player datas
    fscanf(file, "%d\n", &player->playerHealth);
    fscanf(file, "%d\n", &player->playerStrength);
    fscanf(file, "%d\n", &player->playerNumberOfKills);
    fscanf(file, "%d\n", &player->playerRecoveryCount);
    fscanf(file, "%d\n", &player->playerInventoryCount);

    // load player inventory
    for (int i = 0; i < player->playerInventoryCount; i++)
    {
        player->playerInventory[i] = malloc(sizeof(Item));
        if (!player->playerInventory[i])
        {
            printf("Memory allocation failed for inventory item %d\n", i);
            fclose(file);
            return false;
        }

        fgets(player->playerInventory[i]->itemName, MAX_NAME_LEN, file);
        player->playerInventory[i]->itemName[strcspn(player->playerInventory[i]->itemName, "\n")] = 0;
        fscanf(file, "%d\n", &player->playerInventory[i]->itemStrength);
        fscanf(file, "%d\n", &player->playerInventory[i]->itemHealth);
    }

    // loading room data
    for (int i = 0; i < 6; i++)
    {
        fscanf(file, "%d\n", &rooms[i].roomId);
        fgets(rooms[i].roomDescription, 250, file);
        rooms[i].roomDescription[strcspn(rooms[i].roomDescription, "\n")] = 0;

        fscanf(file, "%d\n", &rooms[i].roomItemCount);

        //  loading room items
        for (int j = 0; j < rooms[i].roomItemCount; j++)
        {
            rooms[i].roomItems[j] = malloc(sizeof(Item));
            if (!rooms[i].roomItems[j])
            {
                printf("Memory allocation failed for room item %d in room %d\n", j, i);
                fclose(file);
                return false;
            }

            fgets(rooms[i].roomItems[j]->itemName, MAX_NAME_LEN, file);
            rooms[i].roomItems[j]->itemName[strcspn(rooms[i].roomItems[j]->itemName, "\n")] = 0;
            fscanf(file, "%d\n", &rooms[i].roomItems[j]->itemStrength);
            fscanf(file, "%d\n", &rooms[i].roomItems[j]->itemHealth);
        }

        // loading room creature
        int hasCreature;
        fscanf(file, "%d\n", &hasCreature);
        if (hasCreature)
        {
            rooms[i].roomCreature = malloc(sizeof(Creature));
            if (!rooms[i].roomCreature)
            {
                printf("Memory allocation failed for creature in room %d\n", i);
                fclose(file);
                return false;
            }

            fgets(rooms[i].roomCreature->creatureName, MAX_NAME_LEN, file);
            rooms[i].roomCreature->creatureName[strcspn(rooms[i].roomCreature->creatureName, "\n")] = 0;
            fscanf(file, "%d\n", &rooms[i].roomCreature->creatureHealth);
            fscanf(file, "%d\n", &rooms[i].roomCreature->creatureStrength);
        }
        else
        {
            if (rooms[i].roomCreature)              // free any existing creature in the room

            {
                free(rooms[i].roomCreature);
                rooms[i].roomCreature = NULL;
            }
        }
    }

    fclose(file);
    printf("Game loaded successfully. Continue your adventure!\n");
    return true;
}

