
// Pas eu le temps de faire fonctionner le script pour ajouter des variantes

document.addEventListener("DOMContentLoaded", function () {
    let collectionHolder = document.querySelector(".variant-collection");
    let addVariantButton = document.createElement("button");
    addVariantButton.innerText = "Ajouter une variante";
    addVariantButton.type = "button";
    addVariantButton.classList.add("btn", "btn-success", "mt-2");

    collectionHolder.appendChild(addVariantButton);

    let index = collectionHolder.querySelectorAll(".variant-item").length;

    addVariantButton.addEventListener("click", function () {
        let prototype = collectionHolder.dataset.prototype;
        let newForm = prototype.replace(/__name__/g, index);
        let div = document.createElement("div");
        div.classList.add("variant-item");
        div.innerHTML = newForm;

        let deleteButton = document.createElement("button");
        deleteButton.innerText = "Supprimer";
        deleteButton.type = "button";
        deleteButton.classList.add("btn", "btn-danger", "mt-1");
        deleteButton.addEventListener("click", function () {
            div.remove();
        });

        div.appendChild(deleteButton);
        collectionHolder.appendChild(div);
        index++;
    });
});
