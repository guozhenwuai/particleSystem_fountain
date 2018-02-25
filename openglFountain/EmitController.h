#pragma once
#include "Emitter.h"
#include <map>

struct EmitterUnit {
	Emitter *emitter;
	float factor;
	EmitterUnit()
		: emitter(NULL)
		, factor(1.0f) {}
	EmitterUnit(Emitter *e, float f)
		: emitter(e)
		, factor(f) {}
};

class EmitController
{
public:
	EmitController();
	~EmitController();
	void addRotateEmitter(std::string group, Emitter *emitter, float factor);
	void addShiftEmitter(std::string group, Emitter *emitter, float factor);
	void addWaveEmitter(std::string group, Emitter *emitter, float factor);
	void addBlossomEmitter(std::string group, Emitter *emitter, float factor);
	void addFloodEmitter(std::string group, Emitter *emitter, float factor);
	void rotate(std::string group, float delta);
	void shift(std::string group, float delta);
	void wave(std::string group, float delta);
	void blossom(std::string group, float delta);
	void flood(std::string group, float delta);
	void clear();
	void resetSpeed(std::string group);

private:
	std::map<std::string, std::vector<EmitterUnit>> rotateMap;
	std::map<std::string, std::vector<EmitterUnit>> shiftMap;
	std::map<std::string, std::vector<EmitterUnit>> waveMap;
	std::map<std::string, std::vector<EmitterUnit>> blossomMap;
	std::map<std::string, std::vector<EmitterUnit>> floodMap;
};

