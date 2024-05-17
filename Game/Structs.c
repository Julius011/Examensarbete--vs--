#include "Structs.h"

void LoadAllTextures(Texture2D textures[])
{
    // Players sprites
    textures[TEXTURE_PLAYER_IDLE] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/player/playerIdle.png");
    textures[TEXTURE_PLAYER_DOWN] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/player/playerDown.png");
    textures[TEXTURE_PLAYER_UP] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/player/playerUp.png");
    textures[TEXTURE_PLAYER_LEFT] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/player/playerLeft.png");
    textures[TEXTURE_PLAYER_RIGHT] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/player/playerRight.png");

    // Enemy sprites (Skeleton)
    textures[TEXTURE_SKELETON] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/enemy/skeleton.png");

    // Object sprites

    // Background sprites
    textures[TEXTURE_BACKGROUND_MAZE] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/background/backgroundMaze.png");
    textures[TEXTURE_BACKGROUND_DM] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/background/backgroundDM.png");

    // Backgorund sprites (Turn order)
    textures[TEXTURE_BACKGROUND_TURN_PLAYER] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/background/turnPlayer.png");
    textures[TEXTURE_BACKGROUND_TURN_DM] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/background/turnDM.png");

    // Menu sprites (Movement menu )
    textures[TEXTURE_MENU_MOVE_HIGHER_UP] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/move/menuMoveHigherUp.png");
    textures[TEXTURE_MENU_MOVE_HIGHER_DOWN] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/move/menuMoveHigherDown.png");
    textures[TEXTURE_MENU_MOVE_HIGHER_LEFT] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/move/menuMoveHigherLeft.png");
    textures[TEXTURE_MENU_MOVE_HIGHER_RIGHT] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/move/menuMoveHigherRight.png");
    textures[TEXTURE_MENU_MOVE_LOWER_UP] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/move/menuMoveLowerUp.png");
    textures[TEXTURE_MENU_MOVE_LOWER_DOWN] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/move/menuMoveLowerDown.png");
    textures[TEXTURE_MENU_MOVE_LOWER_LEFT] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/move/menuMoveLowerLeft.png");
    textures[TEXTURE_MENU_MOVE_LOWER_RIGHT] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/move/menuMoveLowerRight.png");

    // Menu sprites (Steps menu )
    textures[TEXTURE_MENU_STEPS_HIGHER_ONE] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/move/menuStepsHigherOne.png");
    textures[TEXTURE_MENU_STEPS_HIGHER_TWO] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/move/menuStepsHigherTwo.png");
    textures[TEXTURE_MENU_STEPS_HIGHER_THREE] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/move/menuStepsHigherThree.png");
    textures[TEXTURE_MENU_STEPS_LOWER_ONE] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/move/menuStepsLowerOne.png");
    textures[TEXTURE_MENU_STEPS_LOWER_TWO] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/move/menuStepsLowerTwo.png");
    textures[TEXTURE_MENU_STEPS_LOWER_THREE] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/move/menuStepsLowerThree.png");

    // Menu sprites (Equpment menu)
    textures[TEXTURE_MENU_EQUIPMENT] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuEquipment.png");
    textures[TEXTURE_MENU_EQUIPMENT_SLOT_SWORD] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuEquipmentSword.png");
    textures[TEXTURE_MENU_EQUIPMENT_SLOT_SHIELD] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuEquipmentShield.png");
    textures[TEXTURE_MENU_EQUIPMENT_SLOT_ITEM] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuEquipmentItem.png");
    textures[TEXTURE_MENU_EQUIPMENT_SLOT_HEAD] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuEquipmentHeadgear.png");
    textures[TEXTURE_MENU_EQUIPMENT_SLOT_CHEST] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuEquipmentChestgear.png");
    textures[TEXTURE_MENU_EQUIPMENT_SLOT_LEGS] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuEquipmentLeggear.png");
    textures[TEXTURE_MENU_EQUIPMENT_SLOT_BOOTS] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuEquipmentBootgear.png");

    // Menu sprites (Inventory menu)
    textures[TEXTURE_MENU_INVENTORY] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuInventory.png");
    textures[TEXTURE_MENU_INVENTORY_ITEMS] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuInventoryItems.png");
    textures[TEXTURE_MENU_INVENTORY_WEAPONS] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuInventoryWeapons.png");
    textures[TEXTURE_MENU_INVENTORY_ARMOR] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuInventoryArmor.png");
    textures[TEXTURE_MENU_INVENTORY_NOTES] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuInventoryNotes.png");

    // Battle menu
    textures[TEXTURE_BATTLE_ATTACK] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/battle/battleSlotAttack.png");
    textures[TEXTURE_BATTLE_DEFENCE] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/battle/battleSlotDefence.png");
    textures[TEXTURE_BATTLE_ITEM] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/battle/battleSlotItem.png");
    textures[TEXTURE_BATTLE_RUN] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/battle/battleSlotRun.png");
}