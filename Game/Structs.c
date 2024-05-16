#include "Structs.h"

void LoadAllTextures(Texture2D textures[])
{
    // Players sprites
    textures[TEXTURE_PLAYER] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/player/tempPlayer.png");
    textures[TEXTURE_PLAYER_DOWN] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/player/player_down.png");
    textures[TEXTURE_PLAYER_UP] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/player/player_up.png");
    textures[TEXTURE_PLAYER_LEFT] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/player/player_left.png");
    textures[TEXTURE_PLAYER_RIGHT] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/player/player_right.png");

    // Enemy sprites (Skeleton)
    textures[TEXTURE_SKELETON] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/enemy/skeleton.png");

    // Object sprites

    // Background sprites
    textures[TEXTURE_BACKGROUND_MAZE] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/background/mazeTempBG.png");
    textures[TEXTURE_BACKGROUND_MAIN] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/background/bg_DM.png");

    // Menu sprites (movement menu)
    textures[TEXTURE_MENU_PUPUPHIGHERBUTTON1] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/move/popUpHigherButton1.png");
    textures[TEXTURE_MENU_PUPUPHIGHERBUTTON2] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/background/popUpHigherButton2.png");
    textures[TEXTURE_MENU_PUPUPHIGHERBUTTON3] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/move/popUpHigherButton3.png");
    textures[TEXTURE_MENU_PUPUPHIGHERBUTTON4] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/move/popUpHigherButton4.png");
    textures[TEXTURE_MENU_PUPUPLOWERBUTTON1] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/move/popUpLowerButton1.png");
    textures[TEXTURE_MENU_PUPUPLOWERBUTTON2] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/move/popUpLowerButton2.png");
    textures[TEXTURE_MENU_PUPUPLOWERBUTTON3] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/move/popUpLowerButton3.png");
    textures[TEXTURE_MENU_PUPUPLOWERBUTTON4] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/move/popUpLowerButton4.png");

    // Menu sprites (Equpment menu)
    textures[TEXTURE_MENU_EQUIPMENT] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuEquipment.png");
    textures[TEXTURE_MENU_EQUIPMENTSLOTSWORD] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuEquipmentSword.png");
    textures[TEXTURE_MENU_EQUIPMENTSLOTSHIELD] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuEquipmentShield.png");
    textures[TEXTURE_MENU_EQUIPMENTSLOTITEM] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuEquipmentItem.png");
    textures[TEXTURE_MENU_EQUIPMENTSLOTHEAD] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuEquipmentHeadgear.png");
    textures[TEXTURE_MENU_EQUIPMENTSLOTCHEST] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuEquipmentChestgear.png");
    textures[TEXTURE_MENU_EQUIPMENTSLOTLEGS] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuEquipmentLeggear.png");
    textures[TEXTURE_MENU_EQUIPMENTSLOTBOOTS] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuEquipmentBootgear.png");

    // Menu sprites (Inventory menu)
    textures[TEXTURE_MENU_INVENTORY] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuInventory.png");
    textures[TEXTURE_MENU_INVENTORYITEMS] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuInventoryItems.png");
    textures[TEXTURE_MENU_INVENTORYWEAPONS] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuInventoryWeapons.png");
    textures[TEXTURE_MENU_INVENTORYARMOR] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuInventoryArmor.png");
    textures[TEXTURE_MENU_INVENTORYNOTES] = LoadTexture("E:/HDDFolders/Programming/C/Game/Game/sprites/menu/EqInvSet/menuInventoryNotes.png");
}