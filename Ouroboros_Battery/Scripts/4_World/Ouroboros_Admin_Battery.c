class Ouroboros_Admin_Battery: Battery9V
{
	void Ouroboros_Admin_Battery()
	{
		if (GetGame().IsServer())
		{
			SetAllowDamage(false);
		}
	}

	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();
		RestoreEnergy();
	}

	override void OnEnergyConsumed()
	{
		super.OnEnergyConsumed();
		RestoreEnergy();
	}

	protected void RestoreEnergy()
	{
		if (!GetGame().IsServer() || !HasEnergyManager())
		{
			return;
		}

		ComponentEnergyManager energyManager = GetCompEM();
		float missingEnergy = energyManager.GetEnergyMax() - energyManager.GetEnergy();
		if (missingEnergy > 0)
		{
			energyManager.AddEnergy(missingEnergy);
		}
	}
}
