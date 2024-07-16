import yaml

code = """
- header: {name: 'Invariant $p_T$ spectra measured for $bar{p}$ '}
  qualifiers:
  - {name: '$p_T$', value: '$U+U$ $60-80\%$'}
  values:
  - value: 0.053995
    errors:
    - {symerror: 0.000224899, label: 'stat.'}
    - {symerror: 5.36001e-06, label: 'sys.'}
  - value: 0.058642
    errors:
    - {symerror: 0.000231411, label: 'stat.'}
    - {symerror: 6.32231e-06, label: 'sys.'}
  - value: 0.0519958
    errors:
    - {symerror: 0.000209582, label: 'stat.'}
    - {symerror: 4.97044e-06, label: 'sys.'}
  - value: 0.0417189
    errors:
    - {symerror: 0.000176024, label: 'stat.'}
    - {symerror: 3.19981e-06, label: 'sys.'}
  - value: 0.0330997
    errors:
    - {symerror: 0.000148739, label: 'stat.'}
    - {symerror: 1.85928e-06, label: 'sys.'}
  - value: 0.0258595
    errors:
    - {symerror: 0.000124944, label: 'stat.'}
    - {symerror: 1.13484e-06, label: 'sys.'}
  - value: 0.0198103
    errors:
    - {symerror: 0.0001053, label: 'stat.'}
    - {symerror: 6.66008e-07, label: 'sys.'}
  - value: 0.0147719
    errors:
    - {symerror: 8.66227e-05, label: 'stat.'}
    - {symerror: 3.70312e-07, label: 'sys.'}
  - value: 0.0108333
    errors:
    - {symerror: 7.08937e-05, label: 'stat.'}
    - {symerror: 1.8257e-07, label: 'sys.'}
  - value: 0.00780402
    errors:
    - {symerror: 5.75492e-05, label: 'stat.'}
    - {symerror: 9.47424e-08, label: 'sys.'}
  - value: 0.00573422
    errors:
    - {symerror: 4.76958e-05, label: 'stat.'}
    - {symerror: 5.11513e-08, label: 'sys.'}
  - value: 0.00427305
    errors:
    - {symerror: 4.02117e-05, label: 'stat.'}
    - {symerror: 3.09865e-08, label: 'sys.'}
  - value: 0.00310316
    errors:
    - {symerror: 3.31477e-05, label: 'stat.'}
    - {symerror: 1.6342e-08, label: 'sys.'}
  - value: 0.00230801
    errors:
    - {symerror: 2.79211e-05, label: 'stat.'}
    - {symerror: 9.04008e-09, label: 'sys.'}
  - value: 0.00173953
    errors:
    - {symerror: 2.36676e-05, label: 'stat.'}
    - {symerror: 5.13521e-09, label: 'sys.'}
  - value: 0.00124952
    errors:
    - {symerror: 2.05142e-05, label: 'stat.'}
    - {symerror: 2.64961e-09, label: 'sys.'}
  - value: 0.00090955
    errors:
    - {symerror: 1.62705e-05, label: 'stat.'}
    - {symerror: 1.40395e-09, label: 'sys.'}
  - value: 0.000684423
    errors:
    - {symerror: 1.38529e-05, label: 'stat.'}
    - {symerror: 7.94957e-10, label: 'sys.'}
  - value: 0.000546667
    errors:
    - {symerror: 1.22453e-05, label: 'stat.'}
    - {symerror: 5.07156e-10, label: 'sys.'}
  - value: 0.000401362
    errors:
    - {symerror: 1.03804e-05, label: 'stat.'}
    - {symerror: 2.73381e-10, label: 'sys.'}
  - value: 0.000315148
    errors:
    - {symerror: 9.04866e-06, label: 'stat.'}
    - {symerror: 1.68549e-10, label: 'sys.'}
  - value: 0.000248947
    errors:
    - {symerror: 7.93211e-06, label: 'stat.'}
    - {symerror: 1.05174e-10, label: 'sys.'}
  - value: 0.000199707
    errors:
    - {symerror: 6.96983e-06, label: 'stat.'}
    - {symerror: 6.76835e-11, label: 'sys.'}

# Insert your YAML code here
"""

data = yaml.safe_load(code)

with open('outputyaml.txt', 'w') as f:
    for item in data[0]['values']:
        if 'value' in item and item['value'] != '--':
            value = item['value']
            stat_error = item['errors'][0]['symerror'] if 'errors' in item and len(item['errors']) > 0 else 'N/A'
            sys_error = item['errors'][1]['symerror'] if 'errors' in item and len(item['errors']) > 1 else 'N/A'
            f.write(f"{value}\t{stat_error}\t{sys_error}\n")