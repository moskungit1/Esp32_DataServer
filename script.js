function fetchData() {
  fetch('/data')
    .then(response => response.text())
    .then(data => {
      // Convert data to a value between 0 and 1
      let value = Math.min(Math.max(parseFloat(data) / 100, 0), 1);  // Ensure the value is between 0 and 1
      setGaugeValue(document.querySelector(".gauge"), value);
    });
}

function setGaugeValue(gauge, value) {
  if (value < 0 || value > 1) {
    return;
  }

  gauge.querySelector(".gauge__fill").style.transform = `rotate(${value / 2}turn)`;
  gauge.querySelector(".gauge__cover").textContent = `${Math.round(value * 100)}%`;
}

// Fetch data every second
setInterval(fetchData, 1000);
