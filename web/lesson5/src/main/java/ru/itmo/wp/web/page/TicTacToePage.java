package ru.itmo.wp.web.page;

import ru.itmo.wp.web.exception.RedirectException;

import javax.servlet.http.HttpServletRequest;
import java.util.Map;

@SuppressWarnings({"unused"})
public class TicTacToePage {
    private void action(HttpServletRequest request, Map<String, Object> view) {
        State state = getState(request);
        if (state == null) {
            newGame(request, view);
        } else {
            view.put("state", state);
        }
    }

    private State getState(HttpServletRequest request) {
        return (State) request.getSession().getAttribute("state");
    }

    private void onMove(HttpServletRequest request, Map<String, Object> view) {
        String cell = request.getParameterMap().keySet().stream()
                .filter(key -> key.matches("cell_\\d{2}"))
                .findAny()
                .orElse(null);

        if (cell == null) {
            return;
        }

        int row = cell.charAt(5) - '0';
        int column = cell.charAt(6) - '0';
        State state = getState(request);
        view.put("state", state.nextState(row, column));
        throw new RedirectException("/ticTacToe");
    }

    private void newGame(HttpServletRequest request, Map<String, Object> view) {
        State state = new State();
        view.put("state", state);
        request.getSession().setAttribute("state", state);
    }

    public static class State {
        private final int size;
        private boolean crossesMove;
        private Phase phase;
        private int emptyCellCount;
        private final Cell[][] cells;

        public State() {
            this.size = 3;
            this.crossesMove = true;
            this.phase = Phase.RUNNING;
            this.emptyCellCount = size * size;
            this.cells = new Cell[size][size];
        }

        public State nextState(int row, int column) {
            if (!isValid(row, column) || phase != Phase.RUNNING) {
                return this;
            }

            Cell cell = crossesMove ? Cell.X : Cell.O;
            cells[row][column] = cell;
            emptyCellCount--;

            // horizontal
            if (count(row, column, 0, 1)
                    + count(row, column, 0, -1) - 1 >= size) {
                phase = Phase.winOf(cell);
                return this;
            }

            // vertical/diagonal
            for (int deltaColumn = -1; deltaColumn <= 1; ++deltaColumn) {
                if (count(row, column, 1, deltaColumn)
                        + count(row, column, -1, -deltaColumn) - 1 >= size) {
                    phase = Phase.winOf(cell);
                    return this;
                }
            }

            if (emptyCellCount == 0) {
                phase = Phase.DRAW;
            }
            crossesMove = !crossesMove;
            return this;
        }

        private boolean isInBounds(int row, int column) {
            return 0 <= row && row < 3 && 0 <= column && column < 3;
        }

        private boolean isValid(int row, int column) {
            return isInBounds(row, column) && cells[row][column] == null;
        }

        private int count(int row, int column, int deltaRow, int deltaColumn) {
            if (isInBounds(row, column) && cells[row][column] == (crossesMove ? Cell.X : Cell.O)) {
                return 1 + count(row + deltaRow, column + deltaColumn, deltaRow, deltaColumn);
            }
            return 0;
        }

        public int getSize() {
            return size;
        }

        public boolean isCrossesMove() {
            return crossesMove;
        }

        public Phase getPhase() {
            return phase;
        }

        public Cell[][] getCells() {
            return cells;
        }

        public enum Phase {
            RUNNING,
            WON_X,
            WON_O,
            DRAW;

            public static Phase winOf(Cell cell) {
                return Phase.valueOf("WON_" + cell);
            }
        }

        public enum Cell {
            X, O
        }
    }
}
