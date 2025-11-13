#pragma once

#include "ClassPoolThread.h"
#include "Counter.h"

class CounterThreadPool : public ClassPoolThread<Counter>
{};