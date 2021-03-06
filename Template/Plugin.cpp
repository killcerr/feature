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
#include <MC/BiomeHeight.hpp>
#include <MC/BiomeArea.hpp>

Logger logger("feature");

bool placeTree = false, placeHug = false, placeOre = false, placeBlockBlobFeature = false;

void PluginInit()
{
	time_t date;
	time(&date);
	auto localDate = localtime(&date);
	logger.setFile("./logs/feature.logs/"+std::to_string(localDate->tm_year+ 1900)+"."+ std::to_string(localDate->tm_mon) + "."+ std::to_string(localDate->tm_wday) + " "+ std::to_string(localDate->tm_hour) + ":"+ std::to_string(localDate->tm_min) + ":"+std::to_string(localDate->tm_sec));
	logger.info("feature loaded");
	/*BiomeRegistry* biomeRegistry = &Global<Level>->getBiomeRegistry();
	biomeRegistry->forEachBiome([=](Biome& biome) {
		logger.info("name:{},id:{}", biome.getName(), biome.getId());
		});*/
	Biome myBiome(INT_MAX - 1);
	myBiome.setName("myBiome");
}
THook(std::optional<class BlockPos>, "?place@VanillaTreeFeature@@UEBA?AV?$optional@VBlockPos@@@std@@AEAVIBlockWorldGenAPI@@AEBVBlockPos@@AEAVRandom@@AEAVRenderParams@@@Z", class IBlockWorldGenAPI& a1, class BlockPos const& a2, class Random& a3, class RenderParams& a4)
{
	logger.info("placetreefeature:blockpos:x:{},y:{},z:{}", a2.x, a2.y, a2.z);
	std::optional<class BlockPos> result = a2;
	if(placeTree)
		result = original(a1, a2,a3,a4);
	//std::cout << "x:" << result->x << "y:" << result->y << "z:" << result->z;
	return result;
}
THook(bool, "?place@HugeFungusFeature@@UEBA_NAEAVBlockSource@@AEBVBlockPos@@AEAVRandom@@@Z", class BlockSource* a1, class BlockPos const* a2, class Random* a3)
{
	bool  result = 1;
	if(placeHug)
		result = original(a1, a2, a3);

	return result;
}
/*THook(std::optional<class BlockPos>, "?place@OreFeature@@UEBA?AV?$optional@VBlockPos@@@std@@AEAVIBlockWorldGenAPI@@AEBVBlockPos@@AEAVRandom@@AEAVRenderParams@@@Z", class IBlockWorldGenAPI& a1, class BlockPos const& a2, class Random& a3, class RenderParams& a4)
{
	std::optional<class BlockPos> result = a2;
	if (placeOre)
		result = original(a1, a2, a3, a4);
	return result;
}*/
THook(std::optional<class BlockPos>, "?place@NoSurfaceOreFeature@@UEBA?AV?$optional@VBlockPos@@@std@@AEAVIBlockWorldGenAPI@@AEBVBlockPos@@AEAVRandom@@AEAVRenderParams@@@Z", class IBlockWorldGenAPI& a1, class BlockPos const& a2, class Random& a3, class RenderParams& a4)
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
THook(bool, "?place@BlockBlobFeature@@UEBA_NAEAVBlockSource@@AEBVBlockPos@@AEAVRandom@@@Z", class BlockSource& a1, class BlockPos const& a2, class Random& a3)
{
	bool  result = 1;
	if (placeHug)
		result = original(a1, a2, a3);
	return result;
}
THook(const void*, "?getBiomeArea@TheEndGenerator@@UEBA?AVBiomeArea@@AEBVBoundingBox@@I@Z", class BoundingBox const& a1, unsigned int a2)
{
	const BiomeArea biomeArea(a1, a2);
	const void* ret = &biomeArea;
	return ret;
}
