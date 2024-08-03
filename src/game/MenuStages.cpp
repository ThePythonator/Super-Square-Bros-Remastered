#include "MenuStages.hpp"

// IntroStage

void IntroStage::start() {
	intro_timer.stop();

	// Start transition
	set_transition(graphics_objects->transition_ptrs[GRAPHICS_OBJECTS::TRANSITIONS::FADE_TRANSITION]);
	transition->open();
}

bool IntroStage::update(float dt) {
	transition->update(dt);
	intro_timer.update(dt);

	if (transition->is_open()) {
		if (intro_timer.running()) {
			if (intro_timer.time() >= TIMINGS::INTRO_OPEN_TIME) {
				transition->close();
			}
		}
		else {
			intro_timer.reset();
			intro_timer.start();
		}
	}
	else if (transition->is_closed()) {
		// Finish intro
		finish(new TitleStage());
	}

	return true;
}

void IntroStage::render() {
	graphics_objects->graphics_ptr->fill(COLOURS::BLACK);

	// Display the Scorpion Games logo in the centre of the display at LOGO_SCALE
	graphics_objects->spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET]->rect(
		Framework::Rect(0, 8, 4, 4) * SPRITES::SIZE,
		WINDOW::SIZE_HALF / SPRITES::LOGO_SCALE - Framework::VEC_ONES * SPRITES::SIZE_HALF * 4,
		SPRITES::LOGO_SCALE
	);

	transition->render();
}

// TitleStage

void TitleStage::start() {
	// Start transition
	set_transition(graphics_objects->transition_ptrs[GRAPHICS_OBJECTS::TRANSITIONS::FADE_TRANSITION]);
	transition->open();
}

bool TitleStage::update(float dt) {
	transition->update(dt);

	// Update buttons
	for (Framework::Button& button : buttons) {
		button.update(input);

		if (button.pressed() && transition->is_open()) {
			button_selected = button.get_id();
			transition->close();
		}
	}

	if (transition->is_closed()) {
		printf("Moving to new stage...\n");
		finish(new LevelSelectStage()); // TODO: temporary to test LevelSelectStage!

		// Next stage!
		switch (button_selected) {
		case BUTTONS::TITLE::PLAY:
			//finish(new GameStage());
			break;

		case BUTTONS::TITLE::SETTINGS:
			//finish(new SettingsStage());
			break;

		case BUTTONS::TITLE::QUIT:
			// Returning false causes program to exit
			return false;
			// (so we don't need the break)

		default:
			break;
		}
	}

	return true;
}

void TitleStage::render() {
	graphics_objects->graphics_ptr->fill(COLOURS::BLUE);

	graphics_objects->spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET]->sprite(0, Framework::Vec(64, 48));

	transition->render();
}

// PausedStage

//PausedStage::PausedStage(BaseStage* background_stage) : BaseStage() {
//	// Save the background stage so we can still render it, and then go back to it when done
//	_background_stage = background_stage;
//}
//
//bool PausedStage::update(float dt) {
//	transition->update(dt);
//
//	if (input->just_down(Framework::KeyHandler::Key::ESCAPE) || input->just_down(Framework::KeyHandler::Key::P)) {
//		transition->close();
//	}
//
//	if (transition->is_closed()) {
//		if (button_selected == BUTTONS::PAUSED::EXIT) {
//			delete _background_stage;
//			finish(new TitleStage());
//		}
//		else {
//			// Return to game (exit pause)
//			finish(_background_stage);
//		}
//	}
//
//	return true;
//}
//
//void PausedStage::render() {
//	// Render background stage
//	_background_stage->render();
//
//	// Render pause menu
//}