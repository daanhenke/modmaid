<script setup lang="ts">
  const {data: namespaces} = await useAsyncData('namespaces', () => queryContent('/docs/namespaces').find());
  const {data: classes} = await useAsyncData('classes', () => queryContent('/docs/classes').find());

  console.log(namespaces.value, classes.value)
</script>

<template>
  <nav>
    <div v-if="namespaces.length > 0">
      <h2>namespaces</h2>
      <div v-for="ns in namespaces">
        <nuxt-link :to="ns._path">{{ ns.name }}</nuxt-link>
      </div>
    </div>
    <div v-if="classes.length > 0">
      <h2>classes</h2>
      <div v-for="clazz in classes">
        {{ clazz.title }}
      </div>
    </div>
  </nav>
</template>

<style scoped>

</style>
