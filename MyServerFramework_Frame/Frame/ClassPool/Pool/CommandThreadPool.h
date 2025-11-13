#pragma once

#include "ClassBaseTypePoolThread.h"
#include "GameCommand.h"

class CommandThreadPool : public ClassBaseTypePoolThread<GameCommand>
{};