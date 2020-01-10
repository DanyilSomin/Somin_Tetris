#pragma once

#include <array>
#include <vector>

constexpr int TETROMINO_STATE_WIDTH{ 4 };

typedef std::array<std::array<int, TETROMINO_STATE_WIDTH>, TETROMINO_STATE_WIDTH> TState;

const std::vector<TState> OStates{ {std::array<int, 4>{ 1, 1, 0, 0 },
									std::array<int, 4>{ 1, 1, 0, 0 },
									std::array<int, 4>{ 0, 0, 0, 0 },
									std::array<int, 4>{ 0, 0, 0, 0 } } };


const std::vector<TState> JStates{ {std::array<int, 4>{ 1, 0, 0, 0 },
									std::array<int, 4>{ 1, 1, 1, 0 },
									std::array<int, 4>{ 0, 0, 0, 0 },
									std::array<int, 4>{ 0, 0, 0, 0 } },

								   {std::array<int, 4>{ 0, 1, 1, 0 },
									std::array<int, 4>{ 0, 1, 0, 0 },
									std::array<int, 4>{ 0, 1, 0, 0 },
									std::array<int, 4>{ 0, 0, 0, 0 } },

								   {std::array<int, 4>{ 0, 0, 0, 0 },
									std::array<int, 4>{ 1, 1, 1, 0 },
									std::array<int, 4>{ 0, 0, 1, 0 },
									std::array<int, 4>{ 0, 0, 0, 0 } },

								   {std::array<int, 4>{ 0, 1, 0, 0 },
									std::array<int, 4>{ 0, 1, 0, 0 },
									std::array<int, 4>{ 1, 1, 0, 0 },
									std::array<int, 4>{ 0, 0, 0, 0 } } };


const std::vector<TState> LStates{ {std::array<int, 4>{ 0, 0, 1, 0 },
									std::array<int, 4>{ 1, 1, 1, 0 },
									std::array<int, 4>{ 0, 0, 0, 0 },
									std::array<int, 4>{ 0, 0, 0, 0 } },

								   {std::array<int, 4>{ 0, 1, 0, 0 },
									std::array<int, 4>{ 0, 1, 0, 0 },
									std::array<int, 4>{ 0, 1, 1, 0 },
									std::array<int, 4>{ 0, 0, 0, 0 } },

								   {std::array<int, 4>{ 0, 0, 0, 0 },
									std::array<int, 4>{ 1, 1, 1, 0 },
									std::array<int, 4>{ 1, 0, 0, 0 },
									std::array<int, 4>{ 0, 0, 0, 0 } },

								   {std::array<int, 4>{ 1, 1, 0, 0 },
									std::array<int, 4>{ 0, 1, 0, 0 },
									std::array<int, 4>{ 0, 1, 0, 0 },
									std::array<int, 4>{ 0, 0, 0, 0 } } };


const std::vector<TState> TStates{ {std::array<int, 4>{ 0, 1, 0, 0 },
									std::array<int, 4>{ 1, 1, 1, 0 },
									std::array<int, 4>{ 0, 0, 0, 0 },
									std::array<int, 4>{ 0, 0, 0, 0 } },

								   {std::array<int, 4>{ 0, 1, 0, 0 },
									std::array<int, 4>{ 0, 1, 1, 0 },
									std::array<int, 4>{ 0, 1, 0, 0 },
									std::array<int, 4>{ 0, 0, 0, 0 } },

								   {std::array<int, 4>{ 0, 0, 0, 0 },
									std::array<int, 4>{ 1, 1, 1, 0 },
									std::array<int, 4>{ 0, 1, 0, 0 },
									std::array<int, 4>{ 0, 0, 0, 0 } },

								   {std::array<int, 4>{ 0, 1, 0, 0 },
									std::array<int, 4>{ 1, 1, 0, 0 },
									std::array<int, 4>{ 0, 1, 0, 0 },
									std::array<int, 4>{ 0, 0, 0, 0 } } };


const std::vector<TState> SStates{ {std::array<int, 4>{ 0, 1, 1, 0 },
									std::array<int, 4>{ 1, 1, 0, 0 },
									std::array<int, 4>{ 0, 0, 0, 0 },
									std::array<int, 4>{ 0, 0, 0, 0 } },

								   {std::array<int, 4>{ 1, 0, 0, 0 },
									std::array<int, 4>{ 1, 1, 0, 0 },
									std::array<int, 4>{ 0, 1, 0, 0 },
									std::array<int, 4>{ 0, 0, 0, 0 } } };


const std::vector<TState> ZStates{ {std::array<int, 4>{ 1, 1, 0, 0 },
									std::array<int, 4>{ 0, 1, 1, 0 },
									std::array<int, 4>{ 0, 0, 0, 0 },
									std::array<int, 4>{ 0, 0, 0, 0 } },

								   {std::array<int, 4>{ 0, 1, 0, 0 },
									std::array<int, 4>{ 1, 1, 0, 0 },
									std::array<int, 4>{ 1, 0, 0, 0 },
									std::array<int, 4>{ 0, 0, 0, 0 } } };


const std::vector<TState> IStates{ {std::array<int, 4>{ 0, 0, 0, 0 },
									std::array<int, 4>{ 1, 1, 1, 1 },
									std::array<int, 4>{ 0, 0, 0, 0 },
									std::array<int, 4>{ 0, 0, 0, 0 } },

								   {std::array<int, 4>{ 0, 1, 0, 0 },
									std::array<int, 4>{ 0, 1, 0, 0 },
									std::array<int, 4>{ 0, 1, 0, 0 },
									std::array<int, 4>{ 0, 1, 0, 0 } } };