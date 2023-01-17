// Set up the chart
const chart = new Highcharts.Chart({
    chart: {
        renderTo: 'container-chart1',
        type: 'column',
        options3d: {
            enabled: true,
            alpha: 15,
            beta: 15,
            depth: 50,
            viewDistance: 25
        }
    },
    xAxis: {
        categories: ['1 Client', '2 Clients', '4 Clients', '8 Clients', '20 Clients']
    },
    yAxis: {
        title: {
            enabled: false
        }
    },
    tooltip: {
        headerFormat: '<b>{point.key}</b><br>',
        pointFormat: 'Runtime: {point.y} s'
    },
    title: {
        text: 'Different number of clients',
        align: 'left'
    },
    subtitle: {
        text: 'Runtime',
        align: 'left'
    },
    legend: {
        enabled: false
    },
    plotOptions: {
        column: {
            depth: 25
        }
    },
    series: [{
        data: [26.18869974,
            13.62557065,
            8.46028435,
            8.87584205,
            10.12265550],
        colorByPoint: true
    }]
});
// Set up the chart
const chart2 = new Highcharts.Chart({
    chart: {
        renderTo: 'container-chart2',
        type: 'column',
        options3d: {
            enabled: true,
            alpha: 15,
            beta: 15,
            depth: 50,
            viewDistance: 25
        }
    },
    xAxis: {
        categories: ['JavaScript', 'C++']
    },
    yAxis: {
        title: {
            enabled: false
        }
    },
    tooltip: {
        headerFormat: '<b>{point.key}</b><br>',
        pointFormat: 'Runtime: {point.y} s'
    },
    title: {
        text: 'JavaScript vs. C++',
        align: 'left'
    },
    subtitle: {
        text: 'Runtime',
        align: 'left'
    },
    legend: {
        enabled: false
    },
    plotOptions: {
        column: {
            depth: 25
        }
    },
    series: [{
        data: [8.460284347,
            3.417911139],
        colorByPoint: true
    }]
});

function showValues() {
    document.getElementById('alpha-value').innerHTML = chart.options.chart.options3d.alpha;
    document.getElementById('beta-value').innerHTML = chart.options.chart.options3d.beta;
    document.getElementById('depth-value').innerHTML = chart.options.chart.options3d.depth;
}

// Activate the sliders
document.querySelectorAll('#sliders input').forEach(input => input.addEventListener('input', e => {
    chart.options.chart.options3d[e.target.id] = parseFloat(e.target.value);
    chart2.options.chart.options3d[e.target.id] = parseFloat(e.target.value);
    // showValues();
    chart.redraw(false);
    chart2.redraw(false);
}));

// showValues();