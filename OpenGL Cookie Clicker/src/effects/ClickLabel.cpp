#include "../../header/effects/ClickLabel.h"
#include "../../header/util/Formatter.h"
#include "../../header/game/PlayerData.h"
#include "../../header/display/DisplayManager.h"
#include "../../header/handler/MouseHandler.h"
#include "../../header/handler/CookieHandler.h"
#include "../../header/handler/FontHandler.h"

#include <EOUL\Maths.h>

using namespace EOUL::Math;

ClickLabel::ClickLabel() : Label("+" + Formatter::formatCookies(CookieHandler::get_mouse_click()), { MouseHandler::mouseX + random(-20.0f, 20.0f), DisplayManager::height - MouseHandler::mouseY }, FontHandler::getFont("kavoon", 25.0f), { 1.0f, 1.0f, 1.0f, 1.0f }, TextRenderer::Alignment::Center) {

}