function showDiv(divId) {
  const divs = document.querySelectorAll('.content-div');

  divs.forEach(div => {
    if (div.id === divId) {
      div.classList.add('active');
    } else {
      div.classList.remove('active');
    }
  });
}
