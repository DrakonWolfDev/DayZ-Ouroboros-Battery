#define _ARMA_

class CfgPatches
{
	class OuroborosBattery
	{
		requiredVersion = 0.1; 
		requiredAddons[] = {"DZ_Data","DZ_Gear_Consumables"};
		author = "DrakonWolf";
		version = "1.0";
	};
};

class cfgVehicles
{
	class Inventory_Base;
	class Battery9V: Inventory_Base{};

	// Base class for all Ouroboros batteries.
	// Inherits from the vanilla 9V battery and defines shared properties.
	class Ouroboros_Battery_Base: Battery9V
	{
		scope = 0; 
		weight = 45; 
		itemSize[] = {1,1};
		inventorySlot[] = {"BatteryD"}; 
		
		// Shared energy behaviour used by both admin and player batteries
		class EnergyManager
		{
			hasIcon = 1;
			switchOnAtSpawn = 1;
			isPassiveDevice = 1;
			convertEnergyToQuantity = 1;
			powerSocketsCount = 1;
			compatiblePlugTypes[] = {1};
		};
	};

	// Admin battery: provides effectively infinite power and extremely high durability.
	class Ouroboros_Admin_Battery: Ouroboros_Battery_Base
	{
		scope = 2;
		displayName = "Ouroboros Admin Battery";
		descriptionShort = "An admin battery. Truly infinite power and physically indestructible.";
		
		class EnergyManager: EnergyManager
		{
			energyStorageMax = 999999;
			energyAtSpawn = 999999;
			// Prevents the battery from losing capacity if the item is damaged
			reduceMaxEnergyByDamageCoef = 0; 
		};

		// Extremely high health so the battery will not realistically reach the "Ruined" state
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 999999; // Effectively indestructible by normal gameplay means
				};
			};
		};
	};

	// Player battery: Long-lasting version with standard survival mechanics
	class Ouroboros_Battery: Ouroboros_Battery_Base
	{
		scope = 2;
		displayName = "Ouroboros Battery";
		descriptionShort = "A high-capacity battery source. Highly durable but not infinite.";
		
		class EnergyManager: EnergyManager
		{
			energyStorageMax = 9999;
			energyAtSpawn = 9999; // Adjust to control how much charge the battery spawns with
			
			// If the battery is damaged, its maximum capacity decreases
			reduceMaxEnergyByDamageCoef = 1; 
		};
		
		// Uses vanilla Battery9V damage system (no override)
		// Durability is identical to the base game battery
	};
};