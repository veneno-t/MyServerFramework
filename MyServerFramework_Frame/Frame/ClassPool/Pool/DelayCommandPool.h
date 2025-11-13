#pragma once

#include "ClassPoolThread.h"
#include "DelayCommand.h"

class DelayCommandPool : public ClassPoolThread<DelayCommand>
{};