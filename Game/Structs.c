#include "Structs.h"

void LoadAllTextures(Texture2D textures[])
{
    // Players sprites
    textures[TEXTURE_PLAYER_IDLE] = LoadTexture("./sprites/player/playerIdle.png");
    textures[TEXTURE_PLAYER_DOWN] = LoadTexture("./sprites/player/playerDown.png");
    textures[TEXTURE_PLAYER_UP] = LoadTexture("./sprites/player/playerUp.png");
    textures[TEXTURE_PLAYER_LEFT] = LoadTexture("./sprites/player/playerLeft.png");
    textures[TEXTURE_PLAYER_RIGHT] = LoadTexture("./sprites/player/playerRight.png");

    // Enemy sprites (Skeleton)
    textures[TEXTURE_SKELETON] = LoadTexture("./sprites/enemy/skeleton.png");

    // Object sprites

    // Background sprites
    textures[TEXTURE_BACKGROUND_MAZE] = LoadTexture("./sprites/background/backgroundMaze.png");
    textures[TEXTURE_BACKGROUND_DM] = LoadTexture("./sprites/background/backgroundDM.png");

    // Main menu
    textures[TEXTURE_MENU_MAIN_START] = LoadTexture("./sprites/menu/main/main_menu_start.png");
    textures[TEXTURE_MENU_MAIN_LOAD] = LoadTexture("./sprites/menu/main/main_menu_load.png");
    textures[TEXTURE_MENU_MAIN_UND] = LoadTexture("./sprites/menu/main/main_menu_undefined.png");
    textures[TEXTURE_MENU_MAIN_EXIT] = LoadTexture("./sprites/menu/main/main_menu_exit.png");

    // Backgorund sprites (Turn order)
    textures[TEXTURE_BACKGROUND_TURN_PLAYER] = LoadTexture("./sprites/background/turnPlayer.png");
    textures[TEXTURE_BACKGROUND_TURN_DM] = LoadTexture("./sprites/background/turnDM.png");

    // Menu sprites (Direction menu )
    textures[TEXTURE_MENU_MOVE_HIGHER_UP] = LoadTexture("./sprites/menu/move/menuMoveHigherUp.png");
    textures[TEXTURE_MENU_MOVE_HIGHER_DOWN] = LoadTexture("./sprites/menu/move/menuMoveHigherDown.png");
    textures[TEXTURE_MENU_MOVE_HIGHER_LEFT] = LoadTexture("./sprites/menu/move/menuMoveHigherLeft.png");
    textures[TEXTURE_MENU_MOVE_HIGHER_RIGHT] = LoadTexture("./sprites/menu/move/menuMoveHigherRight.png");
    textures[TEXTURE_MENU_MOVE_LOWER_UP] = LoadTexture("./sprites/menu/move/menuMoveLowerUp.png");
    textures[TEXTURE_MENU_MOVE_LOWER_DOWN] = LoadTexture("./sprites/menu/move/menuMoveLowerDown.png");
    textures[TEXTURE_MENU_MOVE_LOWER_LEFT] = LoadTexture("./sprites/menu/move/menuMoveLowerLeft.png");
    textures[TEXTURE_MENU_MOVE_LOWER_RIGHT] = LoadTexture("./sprites/menu/move/menuMoveLowerRight.png");

    // Menu sprites (Steps menu )
    textures[TEXTURE_MENU_STEPS_HIGHER_ONE] = LoadTexture("./sprites/menu/move/menuStepsHigherOne.png");
    textures[TEXTURE_MENU_STEPS_HIGHER_TWO] = LoadTexture("./sprites/menu/move/menuStepsHigherTwo.png");
    textures[TEXTURE_MENU_STEPS_HIGHER_THREE] = LoadTexture("./sprites/menu/move/menuStepsHigherThree.png");
    textures[TEXTURE_MENU_STEPS_LOWER_ONE] = LoadTexture("./sprites/menu/move/menuStepsLowerOne.png");
    textures[TEXTURE_MENU_STEPS_LOWER_TWO] = LoadTexture("./sprites/menu/move/menuStepsLowerTwo.png");
    textures[TEXTURE_MENU_STEPS_LOWER_THREE] = LoadTexture("./sprites/menu/move/menuStepsLowerThree.png");

    // Menu sprites (Equpment menu)
    textures[TEXTURE_MENU_EQUIPMENT] = LoadTexture("./sprites/menu/EqInvSet/menuEquipment.png");
    textures[TEXTURE_MENU_EQUIPMENT_SLOT_SWORD] = LoadTexture("./sprites/menu/EqInvSet/menuEquipmentSword.png");
    textures[TEXTURE_MENU_EQUIPMENT_SLOT_SHIELD] = LoadTexture("./sprites/menu/EqInvSet/menuEquipmentShield.png");
    textures[TEXTURE_MENU_EQUIPMENT_SLOT_ITEM] = LoadTexture("./sprites/menu/EqInvSet/menuEquipmentItem.png");
    textures[TEXTURE_MENU_EQUIPMENT_SLOT_HEAD] = LoadTexture("./sprites/menu/EqInvSet/menuEquipmentHeadgear.png");
    textures[TEXTURE_MENU_EQUIPMENT_SLOT_CHEST] = LoadTexture("./sprites/menu/EqInvSet/menuEquipmentChestgear.png");
    textures[TEXTURE_MENU_EQUIPMENT_SLOT_LEGS] = LoadTexture("./sprites/menu/EqInvSet/menuEquipmentLeggear.png");
    textures[TEXTURE_MENU_EQUIPMENT_SLOT_BOOTS] = LoadTexture("./sprites/menu/EqInvSet/menuEquipmentBootgear.png");

    // Menu sprites (Inventory menu)
    textures[TEXTURE_MENU_INVENTORY] = LoadTexture("./sprites/menu/EqInvSet/menuInventory.png");
    textures[TEXTURE_MENU_INVENTORY_ITEMS] = LoadTexture("./sprites/menu/EqInvSet/menuInventoryItems.png");
    textures[TEXTURE_MENU_INVENTORY_WEAPONS] = LoadTexture("./sprites/menu/EqInvSet/menuInventoryWeapons.png");
    textures[TEXTURE_MENU_INVENTORY_ARMOR] = LoadTexture("./sprites/menu/EqInvSet/menuInventoryArmor.png");
    textures[TEXTURE_MENU_INVENTORY_NOTES] = LoadTexture("./sprites/menu/EqInvSet/menuInventoryNotes.png");

    // Battle menu
    textures[TEXTURE_BATTLE_ATTACK] = LoadTexture("./sprites/battle/battleSlotAttack.png");
    textures[TEXTURE_BATTLE_DEFENCE] = LoadTexture("./sprites/battle/battleSlotDefence.png");
    textures[TEXTURE_BATTLE_ITEM] = LoadTexture("./sprites/battle/battleSlotItem.png");
    textures[TEXTURE_BATTLE_RUN] = LoadTexture("./sprites/battle/battleSlotRun.png");
}