#pragma once

#include "components/simple_scene.h"


namespace m1
{

    struct Projectile {
		glm::vec2 position;
		glm::vec2 movement;
		Mesh* mesh;
		glm::mat3 modelMatrix;
		int size; // 0 = smaller, 1 = small, 2 = normal, 3 = big, 4 = bigger

    };
    struct Crate {
        glm::vec2 position;
		Mesh* mesh;
		int type; // 0 = basic, 1 = health, 2 = bigger proj, 3 = smaller proj
    };
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        float cx, cy;
        glm::mat3 modelMatrix, modelMatrix1, modelMatrix2;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;
		float translateXB, translateYB;
		float angularStepB;
		float jumpCircleCx, jumpCircleCy, jumpCircleRad;

        // TODO(student): If you need any other class variables, define them here.

		std::vector<float> height_map;
		int terrainWidth;
        glm::vec3 color1, color11, color2, color22, position1, position2, black, green, red, white, green_health, red_health, orange, gray;
        float barrel_l, barrel_h, angle1, angle2;
        float hull_l, hull_h, hull_upper_l, hull_upper_h;
        float gravity;
        float center1, center2, turret_radius;

        glm::vec3 top_tank1, top_tank2;

		float barrel1_angle, barrel2_angle;

        int proj_size, proj_size1, proj_size2;

		std::vector<Projectile> projectiles1, projectiles2;

        std::vector<Crate> crates;
        int max_crates, curr_crates;
		float time_since_last_crate, crate_delay;
        bool crate_spawning;

		glm::vec2 barrel1_tip, barrel2_tip;

        float magnitude, tank1_health, tank2_health, traj_thickness;

		float magnitude1, magnitude2;

        int step, traj_max;

        float smoothing_limit, smoothing_speed;

        float tank_health;

        bool adding_shot_power;

		float health_bar_l, health_bar_h, health_bar_fill_l, health_bar_fill_h, health_bar_offset_l, health_bar_offset_h, health_bar_height;

		float fire_bar_l, fire_bar_h, fire_bar_fill_l, fire_bar_fill_h, fire_bar_offset_l, fire_bar_offset_h, fire_bar_height;

		bool ready_fire1, ready_fire2;

		float fire_delay1, fire_delay2;

		float last_fired1, last_fired2;

        float destroy_radius, destroy_radius1, destroy_radius2;

		float def_accuracy, tank1_accuracy, tank2_accuracy;

        bool auto_fire;

        float def_damage;
		float damage1, damage2;

        float over_heal_decrease;

        bool turn_based;
		bool tank1_turn;

        float turn_time, turn_remaining;

        int tank_shots, tank1_shots, tank2_shots, tank1_shots_remaining, tank2_shots_remaining;

        float fuel, fuel1, fuel2;

        bool fuel_depletion;




    };
}   // namespace m1
