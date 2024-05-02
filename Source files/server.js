const express = require('express');
const { exec } = require('child_process');
const app = express();
const path = require('path');
const port = 3000;

// Middleware to parse JSON bodies
app.use(express.json());

// Route to serve the FrontEnd.html file
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'FrontEnd.html'));
});

// POST route to handle the evaluation of boolean expressions
app.post('/evaluate', (req, res) => {
    const expression = req.body.expression;
    exec(`./main "${expression}"`, (error, stdout, stderr) => {
        if (error) {
            console.error(`Execution error: ${error}`);
            console.error(`stderr: ${stderr}`);
            return res.status(500).json({ result: 'Error evaluating expression', error: stderr });
        }
        res.json({ result: stdout.trim() });
    });
});

// Start the server
app.listen(port, () => {
    console.log(`Server running on port ${port}`);
});

