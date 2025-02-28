#include "lab_m1/tema1/tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/object2D.h"

using namespace std;
using namespace m1;

#define PI 3.14159265

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;

    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?

	cx = corner.x + squareSide / 2;
	cy = corner.y + squareSide / 2;

    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
	angularStep = 0;

	terrainWidth = 1300;

	height_map.resize(terrainWidth);

    for (int i = 0; i < terrainWidth; i++) {
        float x = i * 0.01f;
        height_map[i] = abs((sin(x) + 3 * sin(x / 5) + 0.5 * sin(3 * x)) * 100.f);
    }

	Mesh* terrain = object2D::CreateTerrain(terrainWidth, height_map);
	AddMeshToList(terrain);
	//for (int i = 0; i < terrainWidth; i++) {
	//	printf("hm[%d]: %f\n", i, height_map[i]);
	//}

	

	color1 = glm::vec3(0.1, 0.6, 0.1);
	color11 = glm::vec3(0.1, 0.8, 0.1);
	color2 = glm::vec3(0.6, 0.1, 0.1);
	color22 = glm::vec3(0.4, 0.1, 0.1);
	position1 = glm::vec3(100, 600, 0);
	center1 = position1.x + hull_l / 2;
	position2 = glm::vec3(1100, 600, 0);
	center2 = position2.x + hull_l / 2;
	black = glm::vec3(0.1, 0.1, 0.1);
	white = glm::vec3(1, 1, 1);
	green = glm::vec3(0.1, 0.6, 0.1);
	green_health = glm::vec3(0, 1, 0);
	red = glm::vec3(0.6, 0.1, 0.1);
	red_health = glm::vec3(1, 0, 0);
	orange = glm::vec3(1, 0.5, 0);
	gray = glm::vec3(0.5, 0.5, 0.5);
	hull_l = 40;
	hull_h = 15;
	hull_upper_l = 80;
	hull_upper_h = 20;

	def_accuracy = 0.3;

	tank1_accuracy = def_accuracy;
	tank2_accuracy = def_accuracy;

	def_damage = 10;
	damage1 = def_damage;
	damage2 = def_damage;

	Mesh* tank1Hull1 = object2D::CreateTrapezoid("tank1Hull1", glm::vec3(0, 0, 0), hull_l, hull_h, color1, true);
	AddMeshToList(tank1Hull1);
	Mesh* tank1Hull2 = object2D::CreateTrapezoid("tank1Hull2", glm::vec3(0, hull_h, 0), hull_upper_l, hull_upper_h, color11, false);
	AddMeshToList(tank1Hull2);
	Mesh* tank2Hull1 = object2D::CreateTrapezoid("tank2Hull1", glm::vec3(0, 0, 0), hull_l, hull_h, color2, true);
	AddMeshToList(tank2Hull1);
	Mesh* tank2Hull2 = object2D::CreateTrapezoid("tank2Hull2", glm::vec3(0, hull_h, 0), hull_upper_l, hull_upper_h, color22, false);
	AddMeshToList(tank2Hull2);
	
	top_tank1 = glm::vec3(hull_l / 2, hull_h + hull_upper_h, 0);
	top_tank2 = glm::vec3(hull_l / 2, hull_h + hull_upper_h, 0);

	barrel_l = 70;
	barrel_h = 10;

	turret_radius = 15;

	Mesh* tank1Turret = object2D::CreateSemiDisc("tank1Turret", top_tank1, turret_radius, true, color11);
	AddMeshToList(tank1Turret);
	Mesh* tank1Barrel = object2D::CreateRectangle("tank1Barrel", top_tank1, barrel_l, barrel_h, turret_radius, black);
	AddMeshToList(tank1Barrel);
	Mesh* tank2Turret = object2D::CreateSemiDisc("tank2Turret", top_tank2, turret_radius, true, color22);
	AddMeshToList(tank2Turret);
	Mesh* tank2Barrel = object2D::CreateRectangle("tank2Barrel", top_tank2, barrel_l, barrel_h, turret_radius, black);
	AddMeshToList(tank2Barrel);
	Mesh* testBarrel = object2D::CreateRectangle("testBarrel", glm::vec3(500, 500, 0), 140, 20, turret_radius, black);
	AddMeshToList(testBarrel);
	proj_size = 2;
	proj_size1 = proj_size;
	proj_size2 = proj_size;
	Mesh* testProjectile = object2D::CreateSemiDisc("projectile2", glm::vec3(0, 0, 0), 6, false, black);
	AddMeshToList(testProjectile);
	Mesh* smallProjectile = object2D::CreateSemiDisc("projectile1", glm::vec3(0, 0, 0), 4, false, black);
	AddMeshToList(smallProjectile);
	Mesh* smallerProjectile = object2D::CreateSemiDisc("projectile0", glm::vec3(0, 0, 0), 3, false, black);
	AddMeshToList(smallerProjectile);
	Mesh* bigProjectile = object2D::CreateSemiDisc("projectile3", glm::vec3(0, 0, 0), 10, false, black);
	AddMeshToList(bigProjectile);
	Mesh* biggerProjectile = object2D::CreateSemiDisc("projectile4", glm::vec3(0, 0, 0), 20, false, black);
	AddMeshToList(biggerProjectile);

	traj_thickness = 1;

	Mesh* trajectory1 = object2D::CreateSemiDisc("trajectory1", glm::vec3(0, 0, 0), traj_thickness, false, white);
	AddMeshToList(trajectory1);
	Mesh* trajectory2 = object2D::CreateSemiDisc("trajectory2", glm::vec3(0, 0, 0), traj_thickness, false, white);
	AddMeshToList(trajectory2);

	barrel1_angle = RADIANS(20);
	barrel2_angle = RADIANS(160);

	projectiles1.resize(0);
	projectiles2.resize(0);

	destroy_radius = 20;
	destroy_radius1 = destroy_radius;
	destroy_radius2 = destroy_radius;

	tank_health = 120;

	tank1_health = 120;
	tank2_health = 120;

	magnitude = 600;

	magnitude1 = magnitude;
	magnitude2 = magnitude;

	adding_shot_power = true;

	auto_fire = false;

	gravity = 800;

	step = 1;

	smoothing_limit = 5;
	smoothing_speed = 200;
	traj_max = 400;

	health_bar_l = 80;
	health_bar_h = 20;
	health_bar_offset_h = 0;
	health_bar_offset_l = 0;
	health_bar_fill_l = health_bar_l - health_bar_offset_l;
	health_bar_fill_h = health_bar_h - health_bar_offset_h;
	health_bar_height = 40;

	Mesh* tank1HealthBarContour = object2D::CreateHealthBarContour("tank1HealthBarContour", 
		glm::vec3(0, hull_h + hull_upper_h + turret_radius + health_bar_height, 0), health_bar_l, health_bar_h, white);
	AddMeshToList(tank1HealthBarContour);
	Mesh* tank1HealthBarFill = object2D::CreateHealthBarFill("tank1HealthBarFill",
		glm::vec3(health_bar_offset_l, hull_h + hull_upper_h + turret_radius + health_bar_height + health_bar_offset_h, 0), health_bar_fill_l, health_bar_fill_h, green_health);
	AddMeshToList(tank1HealthBarFill);

	Mesh* tank2HealthBarContour = object2D::CreateHealthBarContour("tank2HealthBarContour",
		glm::vec3(0, hull_h + hull_upper_h + turret_radius + health_bar_height, 0), health_bar_l, health_bar_h, white);
	AddMeshToList(tank2HealthBarContour);
	Mesh* tank2HealthBarFill = object2D::CreateHealthBarFill("tank2HealthBarFill",
		glm::vec3(health_bar_offset_l, hull_h + hull_upper_h + turret_radius + health_bar_height + health_bar_offset_h, 0), health_bar_fill_l, health_bar_fill_h, green_health);
	AddMeshToList(tank2HealthBarFill);

	Mesh* timeRemainingContour = object2D::CreateHealthBarContour("timeRemainingContour",
		glm::vec3(0, 300, 0), health_bar_l * 2, health_bar_h * 2, white);
	AddMeshToList(timeRemainingContour);
	Mesh* timeRemainingFill = object2D::CreateHealthBarFill("timeRemainingFill",
		glm::vec3(0, 300, 0), health_bar_fill_l * 2, health_bar_fill_h * 2, green);
	AddMeshToList(timeRemainingFill);

	ready_fire1 = true;
	ready_fire2 = true;

	fire_delay1 = 0.5;
	fire_delay2 = 0.5;

	last_fired1 = 0.5;
	last_fired2 = 0.5;

	fire_bar_fill_h = health_bar_fill_h / 2;
	fire_bar_fill_l = health_bar_fill_l / 2;
	fire_bar_h = health_bar_h / 2;
	fire_bar_l = health_bar_l / 2;
	fire_bar_offset_h = 0;
	fire_bar_offset_l = 0;
	fire_bar_height = 20;

	Mesh* tank1FireDelayContour = object2D::CreateHealthBarContour("tank1FireDelayBarContour",
		glm::vec3(0, hull_h + hull_upper_h + turret_radius + health_bar_height + fire_bar_height, 0), fire_bar_l, fire_bar_h, white);
	AddMeshToList(tank1FireDelayContour);
	Mesh* tank1FireDelayFill = object2D::CreateHealthBarFill("tank1FireDelayBarFill",
		glm::vec3(fire_bar_offset_l, hull_h + hull_upper_h + turret_radius + health_bar_height + fire_bar_height + fire_bar_offset_h, 0), 0, fire_bar_fill_h, orange);
	AddMeshToList(tank1FireDelayFill);

	Mesh* tank2FireDelayContour = object2D::CreateHealthBarContour("tank2FireDelayBarContour",
		glm::vec3(0, hull_h + hull_upper_h + turret_radius + health_bar_height + fire_bar_height, 0), fire_bar_l, fire_bar_h, white);
	AddMeshToList(tank2FireDelayContour);
	Mesh* tank2FireDelayFill = object2D::CreateHealthBarFill("tank2FireDelayBarFill",
		glm::vec3(fire_bar_offset_l, hull_h + hull_upper_h + turret_radius + health_bar_height + fire_bar_height + fire_bar_offset_h, 0), 0, fire_bar_fill_h, orange);
	AddMeshToList(tank2FireDelayFill);

	Mesh* tank1FuelContour = object2D::CreateHealthBarContour("tank1FuelBarContour",
		glm::vec3(0, hull_h + hull_upper_h + turret_radius + health_bar_height + fire_bar_height, 0), fire_bar_l, fire_bar_h, white);
	AddMeshToList(tank1FuelContour);
	Mesh* tank1FuelFill = object2D::CreateHealthBarFill("tank1FuelBarFill",
		glm::vec3(fire_bar_offset_l, hull_h + hull_upper_h + turret_radius + health_bar_height + fire_bar_height + fire_bar_offset_h, 0), 0, fire_bar_fill_h, orange);
	AddMeshToList(tank1FuelFill);

	Mesh* tank2FuelContour = object2D::CreateHealthBarContour("tank2FuelBarContour",
		glm::vec3(0, hull_h + hull_upper_h + turret_radius + health_bar_height + fire_bar_height, 0), fire_bar_l, fire_bar_h, white);
	AddMeshToList(tank2FuelContour);
	Mesh* tank2FuelFill = object2D::CreateHealthBarFill("tank2FuelBarFill",
		glm::vec3(fire_bar_offset_l, hull_h + hull_upper_h + turret_radius + health_bar_height + fire_bar_height + fire_bar_offset_h, 0), 0, fire_bar_fill_h, orange);
	AddMeshToList(tank2FuelFill);

	Mesh* healthCrate = object2D::CreateCrate("healthCrate", glm::vec3(0, 0, 0), 30, green, red, 1);
	AddMeshToList(healthCrate);
	Mesh* biggerCrate = object2D::CreateCrate("biggerCrate", glm::vec3(0, 0, 0), 30, gray, orange, 2);
	AddMeshToList(biggerCrate);
	Mesh* smallerCrate = object2D::CreateCrate("smallerCrate", glm::vec3(0, 0, 0), 30, white, orange, 3);
	AddMeshToList(smallerCrate);

	crates.resize(0);
	max_crates = 5;
	curr_crates = 0;
	crate_spawning = false;
	time_since_last_crate = 0;
	crate_delay = 5;

	over_heal_decrease = 10;
	turn_based = false;
	tank1_turn = true;
	tank_shots = 4;
	tank1_shots = tank_shots;
	tank2_shots = tank_shots;
	tank1_shots_remaining = tank1_shots;
	tank2_shots_remaining = tank2_shots;
	fuel = 3;
	fuel1 = fuel;
	fuel2 = fuel;
	fuel_depletion = true;
	turn_time = 7;
	turn_remaining = turn_time;
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.2f, 0.4f, 0.8f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{

	/*printf("FPS: %f\n", 1 / deltaTimeSeconds);*/

	if (turn_based) {
		if (tank1_turn) {
			turn_remaining -= deltaTimeSeconds;
			if (turn_remaining < 0) {
				tank1_turn = false;
				turn_remaining = turn_time;
				fuel1 = fuel;
				tank1_shots_remaining = tank1_shots;
			}
		}
		else {
			turn_remaining -= deltaTimeSeconds;
			if (turn_remaining < 0) {
				tank1_turn = true;
				turn_remaining = turn_time;
				fuel2 = fuel;
				tank2_shots_remaining = tank2_shots;
			}
		}
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(550, 380);
		if (tank1_turn) {
			object2D::UpdateHealthBar(meshes["timeRemainingFill"], health_bar_l * 2, turn_remaining / turn_time * health_bar_fill_l * 2, health_bar_fill_h * 2, green);
		}
		else {
			object2D::UpdateHealthBar(meshes["timeRemainingFill"], health_bar_l * 2, turn_remaining / turn_time * health_bar_fill_l * 2, health_bar_fill_h * 2, red);
		}
		RenderMesh2D(meshes["timeRemainingContour"], shaders["VertexColor"], modelMatrix);
		RenderMesh2D(meshes["timeRemainingFill"], shaders["VertexColor"], modelMatrix);
	}

    modelMatrix = glm::mat3(1);

	if (tank1_health > 120) {
		tank1_health -= over_heal_decrease * deltaTimeSeconds;
	}
	if (tank2_health > 120) {
		tank2_health -= over_heal_decrease * deltaTimeSeconds;
	}

	for (int i = 0; i < terrainWidth - 3; i++) {
		// todo sa incerc cu mai multe puncte
		float diff = height_map[i] - height_map[i + 1];
		if (diff > smoothing_limit) {
			height_map[i] -= smoothing_speed * deltaTimeSeconds;
			height_map[i + 1] += smoothing_speed * deltaTimeSeconds;
		}
		diff = height_map[i + 1] - height_map[i];
		if (diff > smoothing_limit) {
			height_map[i] += smoothing_speed * deltaTimeSeconds;
			height_map[i + 1] -= smoothing_speed * deltaTimeSeconds;
		}
		diff = height_map[i + 1] * 2 - height_map[i] - height_map[i + 2];
		if (diff > smoothing_limit / 2) {
			height_map[i] += smoothing_speed * deltaTimeSeconds / 2;
			height_map[i + 2] += smoothing_speed * deltaTimeSeconds / 2;
			height_map[i + 1] -= smoothing_speed * deltaTimeSeconds;
		}
	}

	object2D::UpdateTerrain(meshes["terrain"], terrainWidth, height_map);

	float hew_health_1 = tank1_health / tank_health * health_bar_fill_l;
	float hew_health_2 = tank2_health / tank_health * health_bar_fill_l;
	float new_green_1 = tank1_health / tank_health;
	float new_green_2 = tank2_health / tank_health;
	float new_red_1 = 1 - new_green_1;
	float new_red_2 = 1 - new_green_2;

	object2D::UpdateHealthBar(meshes["tank1HealthBarFill"], health_bar_l, hew_health_1, health_bar_fill_h, glm::vec3(new_red_1, new_green_1, 0));
	object2D::UpdateHealthBar(meshes["tank2HealthBarFill"], health_bar_l, hew_health_2, health_bar_fill_h, glm::vec3(new_red_2, new_green_2, 0));

	if (!turn_based) {
		if (fuel1 < fuel) {
			fuel1 += deltaTimeSeconds * 0.5;
		}
		if (fuel2 < fuel) {
			fuel2 += deltaTimeSeconds * 0.5;
		}
	}
	object2D::UpdateHealthBar(meshes["tank1FuelBarFill"], health_bar_l, fuel1 / fuel * fire_bar_fill_l, fire_bar_fill_h, red);
	object2D::UpdateHealthBar(meshes["tank2FuelBarFill"], health_bar_l, fuel2 / fuel * fire_bar_fill_l, fire_bar_fill_h, red);

	RenderMesh2D(meshes["terrain"], shaders["VertexColor"], glm::mat3(1));

	center1 = position1.x + hull_l / 2;
	center2 = position2.x + hull_l / 2;


	int A1 = (int)center1 / step;
	int A2 = (int)center2 / step;
	int B1 = A1 + 1;
	int B2 = A2 + 1;

	if (A1 < 0) {
		A1 = 0;
		position1.x = 0;
	}
	if (A2 < 0) {
		A2 = 0;
		position2.x = 0;
	}
	if (A1 > terrainWidth) {
		A1 = terrainWidth - 2;
		position1.x = 1200 - hull_l;
	}
	if (A2 > terrainWidth) {
		A2 = terrainWidth - 2;
		position2.x = 1200 - hull_l;
	}
	if (B1 >= terrainWidth) {
		B1 = terrainWidth - 1;
		position1.x = 1280 - hull_l;
	}
	if (B2 >= terrainWidth) {
		B2 = terrainWidth - 1;
		position2.x = 1280 - hull_l;
	}

	position1.y = height_map[A1];
	position2.y = height_map[A2];

	modelMatrix *= transform2D::Translate(position1.x, position1.y);

	glm::vec2 V1 = glm::vec2(step, height_map[B1] - height_map[A1]);
	angle1 = atan2(V1.y, V1.x);

	modelMatrix *= transform2D::Translate(-hull_l / 2, (hull_h + hull_upper_h) / 2);
	
	if (tank1_health > 0) {
		RenderMesh2D(meshes["tank1HealthBarContour"], shaders["VertexColor"], modelMatrix);
		RenderMesh2D(meshes["tank1HealthBarFill"], shaders["VertexColor"], modelMatrix);
		modelMatrix *= transform2D::Translate(0, -health_bar_height);
		RenderMesh2D(meshes["tank1FuelBarContour"], shaders["VertexColor"], modelMatrix);
		RenderMesh2D(meshes["tank1FuelBarFill"], shaders["VertexColor"], modelMatrix);
		modelMatrix *= transform2D::Translate(0, health_bar_height);
		if (!ready_fire1) {
			modelMatrix *= transform2D::Translate(hull_l / 2, -health_bar_height);
			float new_fire_1 = last_fired1 / fire_delay1 * fire_bar_fill_l;
			object2D::UpdateHealthBar(meshes["tank1FireDelayBarFill"], fire_bar_l, new_fire_1, fire_bar_fill_h, orange);
			last_fired1 += deltaTimeSeconds;
			if (last_fired1 > fire_delay1) {
				ready_fire1 = true;
			}
			modelMatrix *= transform2D::Translate(hull_l / 2, 0);
			RenderMesh2D(meshes["tank1FireDelayBarContour"], shaders["VertexColor"], modelMatrix);
			RenderMesh2D(meshes["tank1FireDelayBarFill"], shaders["VertexColor"], modelMatrix);
			modelMatrix *= transform2D::Translate(-hull_l, health_bar_height);
			
		}
	}
	modelMatrix *= transform2D::Translate(hull_l / 2, -(hull_h + hull_upper_h) / 2);
	modelMatrix *= transform2D::Translate(hull_l / 2, hull_h / 2) * transform2D::Rotate(angle1) * transform2D::Translate(-hull_l / 2, -hull_h / 2);

	if (tank1_health <= 0) {
		modelMatrix *= transform2D::Scale(0, 0);
		modelMatrix *= transform2D::Translate(0, -1000);
		position1.x = 0;
		position1.y = 1000;
	}
	RenderMesh2D(meshes["tank1Hull1"], shaders["VertexColor"], modelMatrix);
	RenderMesh2D(meshes["tank1Hull2"], shaders["VertexColor"], modelMatrix);

	modelMatrix *= transform2D::Translate(top_tank1.x, top_tank1.y);

	RenderMesh2D(meshes["tank1Turret"], shaders["VertexColor"], modelMatrix);

	modelMatrix *= transform2D::Rotate(barrel1_angle) * transform2D::Translate(
		-top_tank1.x + 10, -top_tank1.y - 5);

	barrel1_tip = glm::vec2(top_tank1.x + barrel_l, top_tank1.y + barrel_h / 2);

	RenderMesh2D(meshes["tank1Barrel"], shaders["VertexColor"], modelMatrix);

	modelMatrix *= transform2D::Translate(barrel1_tip.x, barrel1_tip.y);
	barrel1_tip = glm::vec2(modelMatrix * glm::vec3(0, 0, 1));

	glm::vec2 curr_pos = barrel1_tip;
	glm::vec2 movement = glm::vec2(cos(barrel1_angle + angle1), sin(barrel1_angle + angle1)) * magnitude1;

	float time = 0;
	float deltaTime = deltaTimeSeconds / 3;

	if (tank1_health > 0) {
		for (int i = 0; 1; i++) {
			if (curr_pos.x < 0 || curr_pos.x > 1280 || curr_pos.y < 0) {
				break;
			}
			Mesh* trajectory = meshes["trajectory1"];
			RenderMesh2D(trajectory, shaders["VertexColor"], transform2D::Translate(curr_pos.x, curr_pos.y));
			curr_pos += movement * deltaTime;
			movement.y -= (gravity * deltaTime);
			time += deltaTime;
		}
	}

	modelMatrix1 = modelMatrix;

	//printf("pos:  %f  %f barrel_tip: %f %f\n", position1.x, position1.y, barrel1_tip.x, barrel1_tip.y);

	modelMatrix = glm::mat3(1);

	modelMatrix *= transform2D::Translate(position2.x, position2.y);

	glm::vec2 V2 = glm::vec2(step, height_map[B2] - height_map[A2]);
	angle2 = atan2(V2.y, V2.x);

	modelMatrix *= transform2D::Translate(-hull_l / 2, (hull_h + hull_upper_h) / 2);

	if (tank2_health > 0) {
		RenderMesh2D(meshes["tank2HealthBarContour"], shaders["VertexColor"], modelMatrix);
		RenderMesh2D(meshes["tank2HealthBarFill"], shaders["VertexColor"], modelMatrix);
		modelMatrix *= transform2D::Translate(0, -health_bar_height);
		RenderMesh2D(meshes["tank2FuelBarContour"], shaders["VertexColor"], modelMatrix);
		RenderMesh2D(meshes["tank2FuelBarFill"], shaders["VertexColor"], modelMatrix);
		modelMatrix *= transform2D::Translate(0, health_bar_height);
		if (!ready_fire2) {
			modelMatrix *= transform2D::Translate(hull_l / 2, -health_bar_height);
			float new_fire_2 = last_fired2 / fire_delay2 * fire_bar_fill_l;
			object2D::UpdateHealthBar(meshes["tank2FireDelayBarFill"], fire_bar_l, new_fire_2, fire_bar_fill_h, orange);
			last_fired2 += deltaTimeSeconds;
			if (last_fired2 > fire_delay2) {
				ready_fire2 = true;
			}
			modelMatrix *= transform2D::Translate(hull_l / 2, 0);
			RenderMesh2D(meshes["tank2FireDelayBarContour"], shaders["VertexColor"], modelMatrix);
			RenderMesh2D(meshes["tank2FireDelayBarFill"], shaders["VertexColor"], modelMatrix);
			modelMatrix *= transform2D::Translate(-hull_l, health_bar_height);
		}
	}

	modelMatrix *= transform2D::Translate(hull_l / 2, -(hull_h + hull_upper_h) / 2);

	modelMatrix *= transform2D::Translate(hull_l / 2, hull_h / 2) * transform2D::Rotate(angle2) * transform2D::Translate(-hull_l / 2, -hull_h / 2);
	
	if (tank2_health <= 0) {
		modelMatrix *= transform2D::Scale(0, 0);
		modelMatrix *= transform2D::Translate(0, -1000);
		position2.x = 0;
		position2.y = 1000;
	}

	RenderMesh2D(meshes["tank2Hull1"], shaders["VertexColor"], modelMatrix);
	RenderMesh2D(meshes["tank2Hull2"], shaders["VertexColor"], modelMatrix);

	modelMatrix *= transform2D::Translate(top_tank2.x, top_tank2.y);

	RenderMesh2D(meshes["tank2Turret"], shaders["VertexColor"], modelMatrix);

	modelMatrix *= transform2D::Rotate(barrel2_angle) * transform2D::Translate(
		-top_tank2.x + 10, -top_tank2.y - 5);

	barrel2_tip = glm::vec2(top_tank2.x + barrel_l, top_tank2.y + barrel_h / 2);
	
	RenderMesh2D(meshes["tank2Barrel"], shaders["VertexColor"], modelMatrix);

	modelMatrix *= transform2D::Translate(barrel2_tip.x, barrel2_tip.y);
	barrel2_tip = glm::vec2(modelMatrix * glm::vec3(0, 0, 1));

	curr_pos = barrel2_tip;
	movement = glm::vec2(cos(barrel2_angle + angle2), sin(barrel2_angle + angle2)) * magnitude2;

	time = 0;
	deltaTime = deltaTimeSeconds / 3;

	if (tank2_health > 0) {
		for (int i = 0; 1; i++) {
			if (curr_pos.x < 0 || curr_pos.x > 1280 || curr_pos.y < 0) {
				break;
			}
			Mesh* trajectory = meshes["trajectory2"];
			RenderMesh2D(trajectory, shaders["VertexColor"], transform2D::Translate(curr_pos.x, curr_pos.y));
			curr_pos += movement * deltaTime;
			movement.y -= (gravity * deltaTime);
			time += deltaTime;
		}
	}


	modelMatrix2 = modelMatrix;

	for (int i = 0; i < projectiles1.size(); i++) {
		Projectile &p = projectiles1[i];
		p.position += p.movement * deltaTimeSeconds;
		p.movement.y -= (gravity * deltaTimeSeconds);


		int nearest = (int)p.position.x / step;

		if (p.position.x < 10) {
			projectiles1.erase(projectiles1.begin() + i);
		}
		if (p.position.x > 1270) {
			projectiles1.erase(projectiles1.begin() + i);
		}
	
		if (p.position.y < height_map[nearest]) {
			float impact_x = p.position.x;
			float impact_y = p.position.y;
			projectiles1.erase(projectiles1.begin() + i);
			for (int j = nearest - destroy_radius1 / step; j <= nearest + destroy_radius1 / step; j++) {
				if (j >= 0 && j < terrainWidth) {
					float dist = abs(j * step - impact_x);
					if (dist < destroy_radius1) {
						float new_height = impact_y - sqrt(destroy_radius1 * destroy_radius1 - dist * dist);
						height_map[j] = min(height_map[j], new_height);
						height_map[j] = max(height_map[j], 0.f);
					}
				}
			}
		}

		if (position2.x - hull_l < p.position.x && p.position.x < position2.x + hull_upper_l && 
			position2.y < p.position.y && p.position.y < position2.y + hull_h + hull_upper_h) {
			projectiles1.erase(projectiles1.begin() + i);
			tank2_health -= damage1;
		}

		glm::mat3 projectileMatrix = glm::mat3(1);
		projectileMatrix *= transform2D::Translate(p.position.x, p.position.y);
		RenderMesh2D(p.mesh, shaders["VertexColor"], projectileMatrix);

		
	}

	for (int i = 0; i < projectiles2.size(); i++) {
		Projectile &p = projectiles2[i];
		p.position += p.movement * deltaTimeSeconds;
		p.movement.y -= (gravity * deltaTimeSeconds);
		int nearest = (int)p.position.x / step;

		if (p.position.x < 10) {
			projectiles2.erase(projectiles2.begin() + i);
		}
		if (p.position.x > 1270) {
			projectiles2.erase(projectiles2.begin() + i);
		}

		if (p.position.y < height_map[nearest]) {
			float impact_x = p.position.x;
			float impact_y = p.position.y;
			projectiles2.erase(projectiles2.begin() + i);
			for (int j = nearest - destroy_radius2 / step; j <= nearest + destroy_radius2 / step; j++) {
				if (j >= 0 && j < terrainWidth) {
					float dist = abs(j * step - impact_x);
					if (dist < destroy_radius2) {
						float new_height = impact_y - sqrt(destroy_radius2 * destroy_radius2 - dist * dist);
						height_map[j] = min(height_map[j], new_height);
						height_map[j] = max(height_map[j], 0.f);
					}
				}
			}
		}

		if (position1.x - hull_l < p.position.x && p.position.x < position1.x + hull_upper_l && 
			position1.y < p.position.y && p.position.y < position1.y + hull_h + hull_upper_h) {
			projectiles2.erase(projectiles2.begin() + i);
			tank1_health -= damage2;
		}

		glm::mat3 projectileMatrix = glm::mat3(1);
		projectileMatrix *= transform2D::Translate(p.position.x, p.position.y);
		RenderMesh2D(p.mesh, shaders["VertexColor"], projectileMatrix);
	}

	if (crate_spawning) {
		time_since_last_crate += deltaTimeSeconds;
		if (time_since_last_crate > crate_delay) {
			crate_delay = rand() % 5 + 3;
			time_since_last_crate = 0;
			if (curr_crates < max_crates) {
				curr_crates++;
				int type = rand() % 3 + 1;
				float x = rand() % 1200 + 40;
				float y = 720;
				switch (type) {
				case 1:
					crates.push_back({ glm::vec2(x, y), meshes["healthCrate"], 1 });
					break;
				case 2:
					crates.push_back({ glm::vec2(x, y), meshes["biggerCrate"], 2 });
					break;
				case 3:
					crates.push_back({ glm::vec2(x, y), meshes["smallerCrate"], 3 });
					break;
				default:
					break;
				}
			}
		}
	}

	for (int i = 0; i < curr_crates; i++) {
		Crate& c = crates[i];
		c.position.y -= gravity / 2 * deltaTimeSeconds;
		int nearest = (int)c.position.x / step;
		float angle = RADIANS(90);
		if (c.position.y < height_map[nearest]) {
			c.position.y = height_map[nearest];
			int A = (int)c.position.x / step;
			int B = A + 1;
			glm::vec2 V = glm::vec2(step, height_map[B] - height_map[A]);
			angle = atan2(V.y, V.x);
		}
		if (c.position.y < 0) {
			crates.erase(crates.begin() + i);
			curr_crates--;
		}
		glm::mat3 crateMatrix = glm::mat3(1);
		crateMatrix *= transform2D::Translate(c.position.x, c.position.y) * transform2D::Rotate(angle);
		RenderMesh2D(c.mesh, shaders["VertexColor"], crateMatrix);
		if (position1.x - hull_upper_l < c.position.x && c.position.x < position1.x + hull_upper_l && position1.y - hull_h < c.position.y && c.position.y < position1.y + hull_h + hull_upper_h) {
			crates.erase(crates.begin() + i);
			curr_crates--;
			switch (c.type) {
			case 1:
				tank1_health += 40;
				break;
			case 2:
				if (proj_size1 < 4)
				{
					proj_size1++;
					damage1 *= 2;
					fire_delay1 *= 2;
					destroy_radius1 *= 2;
					tank1_shots /= 2;
					tank1_shots_remaining /= 2;
				};
				break;
			case 3:
				if (proj_size1 > 0) {
					proj_size1--;
					damage1 /= 2;
					fire_delay1 /= 2;
					destroy_radius1 /= 2;
					tank1_shots *= 2;
					tank1_shots_remaining *= 2;
				}
				break;
			default:
				break;
			}
		}
		if (position2.x - hull_upper_l < c.position.x && c.position.x < position2.x + hull_upper_l && position2.y - hull_h < c.position.y && c.position.y < position2.y + hull_h + hull_upper_h) {
			crates.erase(crates.begin() + i);
			curr_crates--;
			switch (c.type) {
			case 1:
				tank2_health += 40;
				break;
			case 2:
				if (proj_size2 < 4)
				{
					proj_size2++;
					damage2 *= 2;
					fire_delay2 *= 2;
					destroy_radius2 *= 2;
					tank2_shots /= 2;
					tank2_shots_remaining /= 2;
				};
				break;
			case 3:
				if (proj_size2 > 0) {
					proj_size2--;
					damage2 /= 2;
					fire_delay2 /= 2;
					destroy_radius2 /= 2;
					tank2_shots *= 2;
					tank2_shots_remaining *= 2;
				}
				break;
			default:
				break;
			}
		}
	}


}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_A) && position1.x > 10 && fuel1 > 0 && (!turn_based || tank1_turn)) {
		position1.x -= 200 * deltaTime;
		if (fuel_depletion) {
			fuel1 -= deltaTime * 2;
		}
	}
	if (window->KeyHold(GLFW_KEY_D) && position1.x < 1250 && fuel1 > 0 && (!turn_based || tank1_turn)) {
		position1.x += 200 * deltaTime;
		if (fuel_depletion) {
			fuel1 -= deltaTime * 2;
		}
	}
	if (window->KeyHold(GLFW_KEY_LEFT) && position2.x > 10 && fuel2 > 0 && (!turn_based || !tank1_turn)) {
		position2.x -= 200 * deltaTime;
		if (fuel_depletion) {
			fuel2 -= deltaTime * 2;
		}
	}
	if (window->KeyHold(GLFW_KEY_RIGHT) && position2.x < 1250 && fuel2 > 0 && (!turn_based || !tank1_turn)) {
		position2.x += 200 * deltaTime;
		if (fuel_depletion) {
			fuel2 -= deltaTime * 2;
		}
	}
	if (window->KeyHold(GLFW_KEY_W) && barrel1_angle < RADIANS(190) && (!turn_based || tank1_turn)) {
		barrel1_angle += 1.5 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_S) && barrel1_angle > RADIANS(-10) && (!turn_based || tank1_turn)) {
		barrel1_angle -= 1.5 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_DOWN) && barrel2_angle < RADIANS(190) && (!turn_based || !tank1_turn)) {
		barrel2_angle += 1.5 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_UP) && barrel2_angle > RADIANS(-10) && (!turn_based || !tank1_turn)) {
		barrel2_angle -= 1.5 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_SPACE) && tank1_health > 0 && barrel1_tip.x > 0 && barrel1_tip.x < 1280 && ready_fire1 &&
		auto_fire && (!turn_based || tank1_turn) && tank1_shots_remaining > 0) {
		float inaccuracy = (rand() % 100 - 50) / 100.f * tank1_accuracy;
		Projectile p = { glm::vec2(barrel1_tip.x, barrel1_tip.y), glm::vec2(cos(barrel1_angle + angle1 + inaccuracy),
			sin(barrel1_angle + angle1 + inaccuracy)) * magnitude1, meshes["projectile" + to_string(proj_size1)],
			modelMatrix1, proj_size1};
		projectiles1.push_back(p);
		ready_fire1 = false;
		last_fired1 = 0;
		if (turn_based) {
			tank1_shots_remaining--;
		}
	}
	if (window->KeyHold(GLFW_KEY_ENTER) && tank2_health > 0 && barrel2_tip.x > 0 && barrel2_tip.x < 1280 && ready_fire2 &&
		auto_fire && (!turn_based || !tank1_turn) && tank2_shots_remaining) {
		float inaccuracy = (rand() % 100 - 50) / 100.f * tank2_accuracy;
		Projectile p = { glm::vec2(barrel2_tip.x, barrel2_tip.y), glm::vec2(cos(barrel2_angle + angle2 + inaccuracy),
			sin(barrel2_angle + angle2 + inaccuracy)) * magnitude2, meshes["projectile" + to_string(proj_size2)],
			modelMatrix2, proj_size2};
		projectiles2.push_back(p);
		ready_fire2 = false;
		last_fired2 = 0;
		if (turn_based) {
			tank2_shots_remaining--;
		}
	}
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event

	if (key == GLFW_KEY_X) { // debug
		printf("position1: %f %f\n", position1.x, position1.y);
		printf("position2: %f %f\n", position2.x, position2.y);
	}
	if (key == GLFW_KEY_C) {
		crate_spawning = !crate_spawning;
		if (crate_spawning == false) {
			time_since_last_crate = 0;
		}
	}
	if (key == GLFW_KEY_V) {
		time_since_last_crate = 10;
	}
	if (key == GLFW_KEY_T) {
		turn_based = !turn_based;
		if (turn_based) {
			tank1_turn = true;
			turn_remaining = turn_time;
			fuel1 = fuel;
			fuel2 = fuel;
			tank1_shots_remaining = tank1_shots;
			tank2_shots_remaining = tank2_shots;
		}
		else {
			fuel1 = fuel;
			fuel2 = fuel;
			tank1_shots_remaining = tank1_shots;
			tank2_shots_remaining = tank2_shots;
		}
	}
	if (key == GLFW_KEY_F) {
		fuel_depletion = !fuel_depletion;
	}

	if (key == GLFW_KEY_SPACE && tank1_health > 0 && barrel1_tip.x > 0 && barrel1_tip.x < 1280 && ready_fire1 &&
		!auto_fire && (!turn_based || tank1_turn) && tank1_shots_remaining > 0) {
		float inaccuracy = (rand() % 100 - 50) / 100.f * tank1_accuracy;
		Projectile p = { glm::vec2(barrel1_tip.x, barrel1_tip.y), glm::vec2(cos(barrel1_angle + angle1 + inaccuracy), 
			sin(barrel1_angle + angle1 + inaccuracy)) * magnitude1, meshes["projectile" + to_string(proj_size1)],
			modelMatrix1, proj_size1};
		projectiles1.push_back(p);
		ready_fire1 = false;
		last_fired1 = 0;
		if (turn_based) {
			tank1_shots_remaining--;
		}
	}
	if (key == GLFW_KEY_ENTER && tank2_health > 0 && barrel2_tip.x > 0 && barrel2_tip.x < 1280 && ready_fire2 &&
		!auto_fire && (!turn_based || !tank1_turn) && tank2_shots_remaining > 0) {
		float inaccuracy = (rand() % 100 - 50) / 100.f * tank2_accuracy;
		Projectile p = { glm::vec2(barrel2_tip.x, barrel2_tip.y), glm::vec2(cos(barrel2_angle + angle2 + inaccuracy), 
			sin(barrel2_angle + angle2 + inaccuracy)) * magnitude2, meshes["projectile" + to_string(proj_size2)],
			modelMatrix2, proj_size2};
		projectiles2.push_back(p);
		ready_fire2 = false;
		last_fired2 = 0;
		if (turn_based) {
			tank2_shots_remaining--;
		}
	}
	if (key == GLFW_KEY_Z) {
		auto_fire = !auto_fire;
	}
	if (key == GLFW_KEY_I) {
		tank1_health += 40;
	}
	if (key == GLFW_KEY_O) {
		if (proj_size1 < 4) {
			proj_size1++;
			damage1 *= 2;
			fire_delay1 *= 2;
			destroy_radius1 *= 2;
			tank1_shots /= 2;
			tank1_shots_remaining /= 2;
		}
	}
	if (key == GLFW_KEY_P) {
		if (proj_size1 > 0) {
			proj_size1--;
			damage1 /= 2;
			fire_delay1 /= 2;
			destroy_radius1 /= 2;
			tank1_shots *= 2;
			tank1_shots_remaining *= 2;
		}
	}
	if (key == GLFW_KEY_J) {
		tank2_health += 40;
	}
	if (key == GLFW_KEY_K) {
		if (proj_size2 < 4) {
			proj_size2++;
			damage2 *= 2;
			fire_delay2 *= 2;
			destroy_radius2 *= 2;
			tank2_shots /= 2;
			tank2_shots_remaining /= 2;
		}
	}
	if (key == GLFW_KEY_L) {
		if (proj_size2 > 0) {
			proj_size2--;
			damage2 /= 2;
			fire_delay2 /= 2;
			destroy_radius2 /= 2;
			tank2_shots *= 2;
			tank2_shots_remaining *= 2;
		}
	}
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
