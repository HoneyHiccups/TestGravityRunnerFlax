#include "SceneChanger.h"

SceneChanger::SceneChanger(const SpawnParams& params)
    : Script(params)
{
    // Enable ticking OnUpdate function
    _tickUpdate = true;
}

void SceneChanger::OnEnable()
{
    // Here you can add code that needs to be called when script is enabled (eg. register for events)
    Level::UnloadAllScenesAsync();
    Level::LoadSceneAsync(Scene.ID);
}

void SceneChanger::OnDisable()
{
    // Here you can add code that needs to be called when script is disabled (eg. unregister from events)
}

void SceneChanger::OnUpdate()
{
    // Here you can add code that needs to be called every frame
}
