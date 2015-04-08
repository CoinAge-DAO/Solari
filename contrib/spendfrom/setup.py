from distutils.core import setup
setup(name='btcspendfrom',
      version='1.0',
      description='Command-line utility for solari "coin control"',
      author='Gavin Andresen',
      author_email='gavin@solarifoundation.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
