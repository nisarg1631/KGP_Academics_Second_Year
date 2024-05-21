import setuptools

with open("README.md", "r", encoding="utf-8") as fh:
    long_description = fh.read()

setuptools.setup(
    name="my_package_19CS30031",
    version="0.0.1",
    author="Nisarg Upadhyaya",
    author_email="author@example.com",
    description="Package for Software Engineering Lab Assignment, IIT KGP [Spring 2021]",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/nisarg1631/SE_Python_DS_Asgn/tree/main/Python_DS_Assignment/AssignmentQs2",
    packages=setuptools.find_packages(),
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    python_requires='>=3.6',
)
