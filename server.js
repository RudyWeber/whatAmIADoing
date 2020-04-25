const app = require("express")();
const { PORT = 3000 } = process.env;

const data = [
  { id: 0, value: "A" },
  { id: 1, value: "B" },
  { id: 2, value: "C" },
  { id: 3, value: "D" },
];

app.get("/data/:id", function (req, res) {
  const { id } = req.params;

  const d = data.find(({ id: dataId }) => dataId === +id);

  if (d) {
    res.status(200).json(d);
  } else {
    res.status(404).json({ message: `Data not found at id ${id}` });
  }
});

app.listen(PORT, function () {
  console.log(`Server listening at port ${PORT}`);
});
