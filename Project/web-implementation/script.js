const canvas = document.getElementById('mazeCanvas');
const ctx = canvas.getContext('2d');

let R, C, maze, path;
let startPos = [0, 0];
let endPos = [7, 7];
let currentMode = 'wall'; 
const cellSize = 25;

function setMode(mode) {
    currentMode = mode;
    document.querySelectorAll('.btn-mode').forEach(btn => btn.classList.remove('active'));
    document.getElementById(`mode-${mode}`).classList.add('active');
}

function initMaze() {
    R = parseInt(document.getElementById('rows').value) || 15;
    C = parseInt(document.getElementById('cols').value) || 20;
    
    startPos = [0, 0];
    endPos = [R - 1, C - 1];

    canvas.width = C * cellSize;
    canvas.height = R * cellSize;

    maze = Array(R).fill().map(() => Array(C).fill(0));
    path = [];
    draw();
}

function draw() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    for (let r = 0; r < R; r++) {
        for (let c = 0; c < C; c++) {
            ctx.strokeStyle = '#e0e0e0';
            ctx.strokeRect(c * cellSize, r * cellSize, cellSize, cellSize);

            if (maze[r][c] === 1) ctx.fillStyle = '#2d3436'; // Wall
            else if (path.some(p => p[0] === r && p[1] === c)) ctx.fillStyle = '#fdcb6e'; // Path
            else ctx.fillStyle = '#ffffff';

            if (r === startPos[0] && c === startPos[1]) ctx.fillStyle = '#2ecc71'; 
            if (r === endPos[0] && c === endPos[1]) ctx.fillStyle = '#e74c3c'; 

            ctx.fillRect(c * cellSize + 1, r * cellSize + 1, cellSize - 2, cellSize - 2);
        }
    }
}

function handleInput(e) {
    const rect = canvas.getBoundingClientRect();
    const x = Math.floor((e.clientX - rect.left) / cellSize);
    const y = Math.floor((e.clientY - rect.top) / cellSize);

    if (y >= 0 && y < R && x >= 0 && x < C) {
        path = [];
        
        if (currentMode === 'start') {
            if (maze[y][x] === 1) maze[y][x] = 0;
            startPos = [y, x];
        } else if (currentMode === 'end') {
            if (maze[y][x] === 1) maze[y][x] = 0;
            endPos = [y, x];
        } else {
            if (!(y === startPos[0] && x === startPos[1]) && !(y === endPos[0] && x === endPos[1])) {
                maze[y][x] = 1;
            }
        }
        draw();
    }
}

function solve() {
    const dist = Array(R).fill().map(() => Array(C).fill(Infinity));
    const parent = Array(R).fill().map(() => Array(C).fill(null));
    const pq = [[0, startPos[0], startPos[1]]]; 
    dist[startPos[0]][startPos[1]] = 0;

    const dr = [-1, 1, 0, 0, -1, -1, 1, 1];
    const dc = [0, 0, -1, 1, -1, 1, -1, 1];

    while (pq.length > 0) {
        pq.sort((a, b) => a[0] - b[0]);
        const [d, r, c] = pq.shift();

        if (d > dist[r][c]) continue;
        if (r === endPos[0] && c === endPos[1]) break;

        for (let i = 0; i < 8; i++) {
            const nr = r + dr[i], nc = c + dc[i];
            if (nr >= 0 && nr < R && nc >= 0 && nc < C && maze[nr][nc] === 0) {
                if (dist[r][c] + 1 < dist[nr][nc]) {
                    dist[nr][nc] = dist[r][c] + 1;
                    parent[nr][nc] = [r, c];
                    pq.push([dist[nr][nc], nr, nc]);
                }
            }
        }
    }

    path = [];
    let curr = endPos;
    if (dist[endPos[0]][endPos[1]] === Infinity) {
        alert("No path exists!");
    } else {
        while (curr) {
            path.push(curr);
            curr = parent[curr[0]][curr[1]];
        }
    }
    draw();
}

let isDrawing = false;
canvas.addEventListener('mousedown', (e) => { 
    isDrawing = true; 
    handleInput(e); 
});
window.addEventListener('mouseup', () => isDrawing = false);
canvas.addEventListener('mousemove', (e) => { if (isDrawing && currentMode === 'wall') handleInput(e); });