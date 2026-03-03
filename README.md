## 📚 Laboratory Works Submission Guide

This repository is used for submitting laboratory works.

Please follow the instructions below carefully to ensure your work is reviewed correctly.

---

## 🔀 Step 1. Create a New Branch

For **each laboratory work**, you must create a separate branch using the following naming convention:

```
<labN>/<nickname>
```

### ✅ Examples:

```
lab1/johndoe
lab2/annasmith
lab3/liubomyr
```

Where:

* `labN` — laboratory work number (e.g. lab1, lab2, lab3)
* `nickname` — your GitHub nickname

---

## 📁 Step 2. Create the Correct Directory Structure

Inside your branch, create the following directory structure:

```
labs/<labN>/<nickname>
```

### ✅ Example:

```
labs/lab1/johndoe
```

All files related to the laboratory work must be placed inside this directory.

---

## 💻 Step 3. Add Your Implementation

Inside your folder:

* Add your source code files
* Make sure the project builds and runs correctly
* Follow clean code principles
* Add comments where necessary

Commit your changes with meaningful commit messages.

---

## 🚀 Step 4. Create a Pull Request

When your laboratory work is complete:

1. Push your branch to the repository.
2. Create a **Pull Request (PR)** to the `main` branch.
3. Add a clear description of what was implemented.
4. Wait for review and feedback.

---

## ⚠️ Important Rules

* ❗ Do not commit directly to `main`
* ❗ Do not modify other students' folders
* ❗ Each lab = separate branch
* ❗ Follow the required naming conventions

---

## 📌 Example Workflow

```bash
git checkout -b lab1/johndoe
mkdir -p labs/lab1/johndoe
# add files
git add .
git commit -m "Add lab1 implementation"
git push origin lab1/johndoe
```

Then create a Pull Request on GitHub.

---

Good luck and happy coding! 🚀
