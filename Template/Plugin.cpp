#include "pch.h"
#include <EventAPI.h>
#include <LoggerAPI.h>
#include <MC/Level.hpp>
#include <MC/BlockInstance.hpp>
#include <MC/Block.hpp>
#include <MC/BlockSource.hpp>
#include <MC/Actor.hpp>
#include <MC/Player.hpp>
#include <MC/ItemStack.hpp>
#include <LLAPI.h>
#include <MC/OverworldGenerator.hpp>
#include <MC/Dimension.hpp>
#include <MC/NetherDimension.hpp>
#include <MC/OverworldDimension.hpp>
#include <MC/TheEndDimension.hpp>
#include <MC/NetherGenerator.hpp>
#include <MC/OverworldGenerator.hpp>
#include <MC/TheEndGenerator.hpp>
#include <MC/WorldGenerator.hpp>
#include <MC/VanillaDimensions.hpp>
#include <MC/VanillaFeatures.hpp>
#include <MC/Feature.hpp>
#include <MC/FeatureHelper.hpp>
#include <MC/FeatureRegistry.hpp>
#include <ctime>
#include <HookAPI.h>
#include <MC/Dimension.hpp>
#include <MC/BiomeRegistry.hpp>
#include <thread>
#include <MC/Mob.hpp>
#include <MC/Monster.hpp>
#include <MC/Player.hpp>
#include <MC/Village.hpp>
#include <ScheduleAPI.h>
#include <RegCommandAPI.h>
#include <MC/ITreeFeature.hpp>
#include <MC/CaveFeatureUtils.hpp>
#include <MC/CaveFeature.hpp>
#include <MC/IBlockWorldGenAPI.hpp>
#include <MC/Random.hpp>
#include <MC/Biome.hpp>
#include <MC/Minecraft.hpp>
#include <GlobalServiceAPI.h>
#include <MC/BiomeArea.hpp>
#include <MC/Feature.hpp>
#include <MC/FeatureHelper.hpp>
#include <MC/FeatureRegistry.hpp>
#include <MC/ItemRegistry.hpp>
#include <MC/Item.hpp>
#include <MC/EndDragonFight.hpp>
#include <MC/ChunkSource.hpp>
#include <MC/LevelChunk.hpp>
#include <MC/ServerLevel.hpp>
#include <MC/BlockTypeRegistry.hpp>
#include <MC/BlockLegacy.hpp>
#include <MC/LevelData.hpp>
#include <iostream>
#include <memory>
#include <fstream>
#include <nlohmann/json.hpp>

Logger logger("feature");

namespace Settings 
{
	bool useVanillaRule = false;
}

void PluginInit()
{
	time_t date;
	time(&date);
	auto localDate = localtime(&date);
	logger.setFile("./logs/feature.logs/"+std::to_string(localDate->tm_year+ 1900)+"."+ std::to_string(localDate->tm_mon) + "."+ std::to_string(localDate->tm_wday) + " "+ std::to_string(localDate->tm_hour) + ":"+ std::to_string(localDate->tm_min) + ":"+std::to_string(localDate->tm_sec));
	logger.info("feature loaded");
	//setting file
	struct stat buf;
	if (stat("./plugins/feature/settings.json", &buf) == 0)
	{
		logger.info("get settings file");
		std::ifstream file("./plugins/feature/settings.json");
		json setting = json::parse(file);
		if (setting["rules"].is_object())
		{
			Settings::useVanillaRule = setting["rules"]["useVanillaRules"];
		}
	}
	else
	{
		std::ofstream file("./plugins/feature/settings.json");
		string setting = "{\"rules\":{\"useVanillaRules\":false}}";
		file << setting;
	}
}
/*THook(std::optional<class BlockPos>, "?place@VanillaTreeFeature@@UEBA?AV?$optional@VBlockPos@@@std@@AEAVIBlockWorldGenAPI@@AEBVBlockPos@@AEAVRandom@@AEAVRenderParams@@@Z", class IBlockWorldGenAPI& a1, class BlockPos const& a2, class Random& a3, class RenderParams& a4)
{
	logger.info("placetreefeature:blockpos:x:{},y:{},z:{}", a2.x, a2.y, a2.z);
	std::optional<class BlockPos> result = a2;
	if(placeTree)
		result = original(a1, a2,a3,a4);
	return result;
}
THook(bool, "?place@HugeFungusFeature@@UEBA_NAEAVBlockSource@@AEBVBlockPos@@AEAVRandom@@@Z", class BlockSource* a1, class BlockPos const* a2, class Random* a3)
{
	bool  result = 1;
	if(placeHug)
		result = original(a1, a2, a3);

	return result;
}*/
/*THook(std::optional<class BlockPos>, "?place@OreFeature@@UEBA?AV?$optional@VBlockPos@@@std@@AEAVIBlockWorldGenAPI@@AEBVBlockPos@@AEAVRandom@@AEAVRenderParams@@@Z", class IBlockWorldGenAPI& a1, class BlockPos const& a2, class Random& a3, class RenderParams& a4)
{
	std::optional<class BlockPos> result = a2;
	if (placeOre)
		result = original(a1, a2, a3, a4);
	return result;
}*/
/*THook(std::optional<class BlockPos>, "?place@NoSurfaceOreFeature@@UEBA?AV?$optional@VBlockPos@@@std@@AEAVIBlockWorldGenAPI@@AEBVBlockPos@@AEAVRandom@@AEAVRenderParams@@@Z", class IBlockWorldGenAPI& a1, class BlockPos const& a2, class Random& a3, class RenderParams& a4)
{
	std::optional<class BlockPos> result = a2;
	if (placeOre)
		result = original(a1, a2, a3, a4);
	return result;
}
THook(short, "?getCloudHeight@OverworldDimension@@UEBAFXZ")
{
	return 320;
}
*//*THook(bool, "?place@BlockBlobFeature@@UEBA_NAEAVBlockSource@@AEBVBlockPos@@AEAVRandom@@@Z", class BlockSource& a1, class BlockPos const& a2, class Random& a3)
{
	bool  result = 1;
	if (placeHug)
		result = original(a1, a2, a3);
	return result;
}*/
/*THook(void, "?setup@ChangeSettingCommand@@SAXAEAVCommandRegistry@@@Z", void* self) {
	SymCall("?setup@AbilityCommand@@SAXAEAVCommandRegistry@@@Z", void, void*)(self);
	return original(self);
}*/

/*THook(std::shared_ptr<class LevelChunk>, "?createNewChunk@ChunkSource@@UEAA?AV?$shared_ptr@VLevelChunk@@@std@@AEBVChunkPos@@W4LoadMode@1@_N@Z", ChunkSource* _this, class ChunkPos const* a1, enum ChunkSource::LoadMode a2, bool a3)
{
	return original(_this, a1, a2, a3);
}*/

#include <MC/EndCityFeature.hpp>
THook(bool, "?isFeatureChunk@EndCityFeature@@MEAA_NAEBVBiomeSource@@AEAVRandom@@AEBVChunkPos@@IAEBVIPreliminarySurfaceProvider@@AEBVDimension@@@Z", EndCityFeature* _this, class BiomeSource const* a1, class Random* a2, class ChunkPos const* a3, unsigned int a4, class IPreliminarySurfaceProvider const* a5, class Dimension const* a6)
{
	if (Settings::useVanillaRule == true)
	{
		return original(_this, a1, a2, a3, a4, a5, a6);
	}
	else
	{
		if (a3->x % 4 == 0 && a3->z % 4 == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
#include <MC/AncientCityFeature.hpp>
THook(bool, "?isFeatureChunk@AncientCityFeature@@UEAA_NAEBVBiomeSource@@AEAVRandom@@AEBVChunkPos@@IAEBVIPreliminarySurfaceProvider@@AEBVDimension@@@Z", AncientCityFeature* _this, class BiomeSource const* a1, class Random* a2, class ChunkPos const* a3, unsigned int a4, class IPreliminarySurfaceProvider const* a5, class Dimension const* a6)
{

	if (Settings::useVanillaRule == true)
	{
		return original(_this, a1, a2, a3, a4, a5, a6);
	}
	else
	{
		if (a3->x % 4 == 0 && a3->z % 4 == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
#include <MC/NetherFortressFeature.hpp>
THook(bool, "?isFeatureChunk@NetherFortressFeature@@MEAA_NAEBVBiomeSource@@AEAVRandom@@AEBVChunkPos@@IAEBVIPreliminarySurfaceProvider@@AEBVDimension@@@Z", NetherFortressFeature* _this, class BiomeSource const* a1, class Random* a2, class ChunkPos const* a3, unsigned int a4, class IPreliminarySurfaceProvider const* a5, class Dimension const* a6)
{
	if (Settings::useVanillaRule == true)
	{
		return original(_this, a1, a2, a3, a4, a5, a6);
	}
	else
	{
		if (a3->x % 4 == 0 && a3->z % 4 == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
#include <MC/StrongholdFeature.hpp>
THook(bool, "?isFeatureChunk@StrongholdFeature@@UEAA_NAEBVBiomeSource@@AEAVRandom@@AEBVChunkPos@@IAEBVIPreliminarySurfaceProvider@@AEBVDimension@@@Z", StrongholdFeature* _this, class BiomeSource const* a1, class Random* a2, class ChunkPos const* a3, unsigned int a4, class IPreliminarySurfaceProvider const* a5, class Dimension const* a6)
{
	if (Settings::useVanillaRule == true)
	{
		return original(_this, a1, a2, a3, a4, a5, a6);
	}
	else
	{
		if (a3->x % 4 == 0 && a3->z % 4 == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
#include <MC/MineshaftFeature.hpp>
THook(bool, "?isFeatureChunk@MineshaftFeature@@UEAA_NAEBVBiomeSource@@AEAVRandom@@AEBVChunkPos@@IAEBVIPreliminarySurfaceProvider@@AEBVDimension@@@Z", MineshaftFeature* _this, class BiomeSource const* a1, class Random* a2, class ChunkPos const* a3, unsigned int a4, class IPreliminarySurfaceProvider const* a5, class Dimension const* a6)
{
	if (Settings::useVanillaRule == true)
	{
		return original(_this, a1, a2, a3, a4, a5, a6);
	}
	else
	{
		if (a3->x % 4 == 0 && a3->z % 4 == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
#include <MC/VillageFeature.hpp>
THook(bool, "?isFeatureChunk@VillageFeature@@UEAA_NAEBVBiomeSource@@AEAVRandom@@AEBVChunkPos@@IAEBVIPreliminarySurfaceProvider@@AEBVDimension@@@Z", VillageFeature* _this, class BiomeSource const* a1, class Random* a2 , class ChunkPos const* a3, unsigned int a4, class IPreliminarySurfaceProvider const* a5, class Dimension const* a6)
{
	if (Settings::useVanillaRule == true)
	{
		return original(_this, a1, a2, a3, a4, a5, a6);
	}
	else
	{
		if (a3->x % 4 == 0 && a3->z % 4 == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
#include <MC/WoodlandMansionFeature.hpp>
THook(bool, "?isFeatureChunk@WoodlandMansionFeature@@MEAA_NAEBVBiomeSource@@AEAVRandom@@AEBVChunkPos@@IAEBVIPreliminarySurfaceProvider@@AEBVDimension@@@Z", WoodlandMansionFeature* _this, class BiomeSource const* a1, class Random* a2, class ChunkPos const* a3, unsigned int a4, class IPreliminarySurfaceProvider const* a5, class Dimension const* a6)
{
	if (Settings::useVanillaRule == true)
	{
		return original(_this, a1, a2, a3, a4, a5, a6);
	}
	else
	{
		if (a3->x % 4 == 0 && a3->z % 4 == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
#include <MC/BuriedTreasureFeature.hpp>
THook(bool, "?isFeatureChunk@BuriedTreasureFeature@@MEAA_NAEBVBiomeSource@@AEAVRandom@@AEBVChunkPos@@IAEBVIPreliminarySurfaceProvider@@AEBVDimension@@@Z", BuriedTreasureFeature* _this, class BiomeSource const* a1, class Random* a2, class ChunkPos const* a3, unsigned int a4, class IPreliminarySurfaceProvider const* a5, class Dimension const* a6)
{
	if (Settings::useVanillaRule == true)
	{
		return original(_this, a1, a2, a3, a4, a5, a6);
	}
	else
	{
		if (a3->x % 4 == 0 && a3->z % 4 == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
#include <MC/RuinedPortalFeature.hpp>
THook(bool, "?isFeatureChunk@RuinedPortalFeature@@MEAA_NAEBVBiomeSource@@AEAVRandom@@AEBVChunkPos@@IAEBVIPreliminarySurfaceProvider@@AEBVDimension@@@Z", RuinedPortalFeature* _this, class BiomeSource const* a1, class Random* a2, class ChunkPos const* a3, unsigned int a4, class IPreliminarySurfaceProvider const* a5, class Dimension const* a6)
{
	if (Settings::useVanillaRule == true)
	{
		return original(_this, a1, a2, a3, a4, a5, a6);
	}
	else
	{
		if (a3->x % 4 == 0 && a3->z % 4 == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
#include <MC/BastionFeature.hpp>
THook(bool, "?isFeatureChunk@BastionFeature@@UEAA_NAEBVBiomeSource@@AEAVRandom@@AEBVChunkPos@@IAEBVIPreliminarySurfaceProvider@@AEBVDimension@@@Z", BastionFeature* _this, class BiomeSource const* a1, class Random* a2, class ChunkPos const* a3, unsigned int a4, class IPreliminarySurfaceProvider const* a5, class Dimension const* a6)
{
	if (Settings::useVanillaRule == true)
	{
		return original(_this, a1, a2, a3, a4, a5, a6);
	}
	else
	{
		if (a3->x % 4 == 0 && a3->z % 4 == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
#include <MC/OceanRuinFeature.hpp>
THook(bool, "?isFeatureChunk@OceanRuinFeature@@UEAA_NAEBVBiomeSource@@AEAVRandom@@AEBVChunkPos@@IAEBVIPreliminarySurfaceProvider@@AEBVDimension@@@Z", OceanRuinFeature* _this, class BiomeSource const* a1, class Random* a2, class ChunkPos const* a3, unsigned int a4, class IPreliminarySurfaceProvider const* a5, class Dimension const* a6)
{
	if (Settings::useVanillaRule == true)
	{
		return original(_this, a1, a2, a3, a4, a5, a6);
	}
	else
	{
		if (a3->x % 4 == 0 && a3->z % 4 == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
#include <MC/OceanMonumentFeature.hpp>
THook(bool, "?isFeatureChunk@OceanMonumentFeature@@UEAA_NAEBVBiomeSource@@AEAVRandom@@AEBVChunkPos@@IAEBVIPreliminarySurfaceProvider@@AEBVDimension@@@Z", OceanMonumentFeature* _this, class BiomeSource const* a1, class Random* a2, class ChunkPos const* a3, unsigned int a4, class IPreliminarySurfaceProvider const* a5, class Dimension const* a6)
{
	if (Settings::useVanillaRule == true)
	{
		return original(_this, a1, a2, a3, a4, a5, a6);
	}
	else
	{
		if (a3->x % 4 == 0 && a3->z % 4 == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
/*THook(float, "?getValue@PerlinNoise@@QEBAMAEBVVec3@@@Z", class Vec3 const* a1)
{
	float result = original(a1);
	logger.info("noise::getValue:x:{},y:{},z:{},result:{}", a1->x, a1->y, a1->z, result);
	return result;
}
THook(float, "?getValueNormalized@PerlinNoise@@QEBAMAEBVVec3@@@Z", class Vec3 const* a1)
{
	float result = original(a1);
	logger.info("noise::getValueNormalized:x:{},y:{},z:{},result:{}", a1->x, a1->y, a1->z, result);
	return result;
}*/
/*THook(float, "?getValueNormalized@PerlinSimplexNoise@@QEBAMMM@Z", float a1, float a2)
{
	auto ret = original(a1, a2);
	std::cout << "a1" << a1 << "a2" << a2 << "ret" << ret << std::endl;
	return 0;
}
THook(float, "?getValue@PerlinSimplexNoise@@QEBAMAEBVVec3@@@Z", class Vec3 const* a1)
{
	auto ret = original(a1);
	std::cout << "vec3" << "x" << a1->x << "y" << a1->y << "z" << a1->z << std::endl;
	return 0;
}*/
/*THook(float, "?getValueNormalized@PerlinSimplexNoise@@QEBAMAEBVVec3@@@Z", class Vec3 const* a1)
{
	auto ret = original(a1);
	//std::cout << "vec3" << "x" << a1->x << "y" << a1->y << "z" << a1->z << std::endl;
	return ret;
}
THook(float, "?getValue@PerlinSimplexNoise@@QEBAMMM@Z", float a1, float a2)
{
	auto ret = original(a1, a2);
	//std::cout << "a1" << a1 << "a2" << a2 << "ret" << ret << std::endl;
	return ret;
}*/
/*TInstanceHook(std::shared_ptr<class LevelChunk>, "?createNewChunk@ChunkSource@@UEAA?AV?$shared_ptr@VLevelChunk@@@std@@AEBVChunkPos@@W4LoadMode@1@_N@Z", ChunkSource, class ChunkPos const* a1, enum ChunkSource::LoadMode a2, bool a3)
{
	auto minHeight = this->getDimension().getMinHeight();
	auto height = this->getDimension().getHeight();
	//logger.info("minHeight:{},height:{}", minHeight, height);
	return std::move(original(this, a1, a2, a3));
}*/
/*TInstanceHook(short, "?getHeight@Dimension@@QEBAFXZ", Dimension, void)
{
	return 0;
}*/
/*TInstanceHook(void, "??0WorldGenerator@@QEAA@AEAVDimension@@@Z", WorldGenerator, class Dimension* a1)
{
	logger.info("dimid:{}", a1->getDimensionId());
	return original(this, ::Global<Level>->getDimension(0));
}*/

/*TInstanceHook(WorldGenerator*, "?getWorldGenerator@Dimension@@QEBAPEAVWorldGenerator@@XZ", Dimension, void)
{
	auto dimension = ::Global<Level>->getDimension(1);
	return new WorldGenerator(*dimension);
}*/
#include <MC/ChunkViewSource.hpp>
TInstanceHook(bool, "?postProcess@OverworldGenerator@@UEAA_NAEAVChunkViewSource@@@Z", OverworldGenerator, class ChunkViewSource* a1)
{
	if (Settings::useVanillaRule == true)
	{
		return original(this, a1);
	}
	else
	{
		return true;
	}
}
TInstanceHook(bool, "?postProcess@NetherGenerator@@UEAA_NAEAVChunkViewSource@@@Z", NetherGenerator, class ChunkViewSource* a1)
{
	if (Settings::useVanillaRule == true)
	{
		return original(this, a1);
	}
	else
	{
		return true;
	}
}
TInstanceHook(bool, "?postProcess@TheEndGenerator@@UEAA_NAEAVChunkViewSource@@@Z", OverworldGenerator, class ChunkViewSource* a1)
{
	if (Settings::useVanillaRule == true)
	{
		return original(this, a1);
	}
	else
	{
		return true;
	}
}

TInstanceHook(void, "?buildSurfaces@OverworldGenerator@@QEAAXAEAUThreadData@1@AEAVBlockVolume@@AEAVLevelChunk@@AEBVChunkPos@@AEBVSurfaceLevelCache@@@Z", OverworldGenerator, struct OverworldGenerator::ThreadData* a1, class BlockVolume* a2, class LevelChunk* a3, class ChunkPos const* a4, class SurfaceLevelCache const* a5)
{
	if (Settings::useVanillaRule == true)
	{
		return original(this, a1,a2,a3,a4,a5);
	}
	else
	{
		return;
	}
}
/*TInstanceHook(void, "??1FeatureRootParseContext@FeatureLoading@@QEAA@XZ", FeatureLoading, void)
{
	logger.info("??1FeatureRootParseContext@FeatureLoading@@QEAA@XZ");
	return;
}*/
TInstanceHook(void, "?buildSurfaces@TheEndGenerator@@QEAAXAEAVBlockVolume@@AEBVChunkPos@@AEAVLevelChunk@@@Z", TheEndGenerator, class BlockVolume* a1, class ChunkPos const* a2, class LevelChunk* a3)
{
	if (Settings::useVanillaRule == true)
	{
		return original(this, a1, a2, a3);
	}
	else
	{
		return;
	}
}
TInstanceHook(void, "?buildSurfaces@NetherGenerator@@QEAAXAEAVBlockVolume@@AEAVLevelChunk@@AEBVChunkPos@@@Z", NetherGenerator, class BlockVolume* a1, class ChunkPos const* a2, class LevelChunk* a3)
{
	if (Settings::useVanillaRule == true)
	{
		return original(this, a1, a2, a3);
	}
	else
	{
		return;
	}
}
#include <MC/OreVeinifier.hpp>
#include <MC/VanillaBlocks.hpp>
TInstanceHook(Block const*, "?getVeinBlockOrFallback@OreVeinifier@@QEBAPEBVBlock@@VVec3@@PEBV2@@Z", OreVeinifier, class Vec3 a1, class Block const* a2)
{
	if (Settings::useVanillaRule == true)
	{
		return original(this, a1, a2);
	}
	else
	{
		return Block::create("minecraft:air",0);
	}
}
