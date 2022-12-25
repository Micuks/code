# Automatically created by: scrapyd-deploy

from setuptools import setup, find_packages

setup(
    name         = 'project',
    version      = '1.0',
    packages     = find_packages(),
    entry_points = {'scrapy': ['settings = lianjia.settings']},
    package_data= {'lianjia': ['lianjia/database/Lianjia.db']}
)
