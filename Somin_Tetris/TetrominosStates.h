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


const std::array<int, 5> SCORE_POINTS_COEF{ 0, 40, 100, 300, 1200 }; // score points
const std::array<int, 30> LEVEL_PERIODS{ 1660, 1570, 1480, 1390, 1300, 1210, 1120, 1030, 940,  850,
										 810,  790,  750,  690,  630,  570,  510,  450,  400,  390,
										 340,  300,  225,  250,  220,  190,  160,  130,  100,  80 }; // mswww